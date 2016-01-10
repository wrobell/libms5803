/*
 * libms5803 - MS5803 pressure sensor library
 *
 * Copyright (C) 2014-2016 by Artur Wroblewski <wrobell@pld-linux.org>
 *
 * Also contains code from
 *
 *      http://www.john.geek.nz/2013/02/update-bosch-ms5803-source-raspberry-pi/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <errno.h>
#include <stdint.h>

#ifdef MS5803_DEBUG
#include <stdio.h>
#define DEBUG_LOG(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define DEBUG_LOG(fmt, ...)
#endif

#define BSWAP16(v) (v << 8) & 0xFF00 | (v >> 8) & 0xFF

/* i2c file descriptor */
static int i2c_fd;

/* MS5803 calibration data */
static uint16_t calib_coeff[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/*!
 * Perform ADC read from the sensor.
 *
 * Command is 0x48 or 0x58 - read pressure or temperature with highest
 * accuracy.
 *
 * \param command ADC command.
 */
static uint32_t read_value(uint8_t command) {
    int r;
    uint8_t data[3];

    r = write(i2c_fd, (unsigned char[]) {command}, 1);
    if (r != 1)
        return -1;
    usleep(8250);

    r = write(i2c_fd, (unsigned char[]) {0x00}, 1);
    if (r != 1)
        return -1;

    r = read(i2c_fd, data, 3);
    if (r != 3)
        return -1;

    DEBUG_LOG(
        "MS5803 DEBUG: value for command %x: %d\n", command,
        (data[0] << 16) | (data[1] << 8) | data[2]
    );
    return (data[0] << 16) | (data[1] << 8) | data[2];
}

/*!
 * Calculate pressure and temperature using D1, D2 values read from sensor
 * and the calibration coefficients.
 */
static void calculate(uint32_t d1, uint32_t d2, int32_t *pressure, int32_t *temperature) {
    int32_t d_t, temp, p;
    int64_t off, sens, off_2, sens_2, t_2;
    int64_t c1, c2, c3, c4, c5, c6;

    c1 = calib_coeff[1];
    c2 = calib_coeff[2];
    c3 = calib_coeff[3];
    c4 = calib_coeff[4];
    c5 = calib_coeff[5];
    c6 = calib_coeff[6];

    d_t = d2 - (c5 << 8);
    temp = 2000 + ((d_t * c6) >> 23);
    off = (c2 << 16) + ((c4 * d_t) >> 7);
    sens = (c1 << 15) + ((c3 * d_t) >> 8);
    p = (((d1 * sens) >> 21) - off) >> 15;

    DEBUG_LOG("MS5803 DEBUG: d_t: %d\n", d_t);
    DEBUG_LOG("MS5803 DEBUG: temp: %d\n", temp);
    DEBUG_LOG("MS5803 DEBUG: off: %d\n", off);
    DEBUG_LOG("MS5803 DEBUG: sens: %d\n", sens);
    DEBUG_LOG("MS5803 DEBUG: p: %d\n", p);

    if (temp >= 2000) {
        DEBUG_LOG("MS5803 DEBUG: temp >= 20\n");
        t_2 = (7 * ((int64_t) d_t * d_t)) >> 37;
        off_2 = ((temp - 2000) * (temp - 2000)) >> 4;
        sens_2 = 0;
    } else {
        DEBUG_LOG("MS5803 DEBUG: temp < 20\n");
        t_2 = (3 * (int64_t) d_t * d_t) >> 33;
        off_2 = (3 * (temp - 2000) * (temp - 2000)) >> 2;
        sens_2 = (5 * (temp - 2000) * (temp - 2000)) >> 3;

        if (temp < 1500) {
            DEBUG_LOG("MS5803 DEBUG: temp < 15\n");
            t_2 = (3 * (int64_t) d_t * d_t) >> 33;
            off_2 = off_2 + 7 * (temp + 1500) * (temp + 1500);
            sens_2 = sens_2 + 4 * (temp + 1500) * (temp + 1500);
        }
    }

    temp = temp - t_2;
    off = off - off_2;
    sens = sens - sens_2;

    *pressure = p;
    *temperature = temp;
}

/*
 * Public API implementation.
 */

int ms5803_init(const char *f_dev, unsigned char address) {
    int r, i;

    if ((i2c_fd = open(f_dev, O_RDWR)) < 0)
        return -1;

    /* set the port options and set the address of the device */
    if (ioctl(i2c_fd, I2C_SLAVE, address) < 0)
        return -1;

    /* reset the sensor */
    r = write(i2c_fd, (unsigned char[]) {0x1e}, 1);
    if (r != 1)
        return -1;
    usleep(3000);

    /* read the calibration coefficients and store them in `calib_coeff`
       array */
    for (i = 0; i < 8; i++) {
        r = write(i2c_fd, (uint8_t[]) {0xa0 + i * 2}, 1);
        if (r != 1)
            return -1;

        r = read(i2c_fd, &calib_coeff[i], 2);
        calib_coeff[i] = BSWAP16(calib_coeff[i]);
        DEBUG_LOG("MS5803 DEBUG: calibration coefficient %d: %d\n", i, calib_coeff[i]);
        if (r != 2)
            return -1;
    }

    return 0;
}

int ms5803_read(int32_t *pressure, int32_t *temperature) {
    uint32_t d1;
    uint32_t d2;

    d1 = read_value(0x48);
    if (d1 == -1)
        return -1;

    d2 = read_value(0x58);
    if (d2 == -1)
        return -1;

    calculate(d1, d2, pressure, temperature);
    return 0;
}

int ms5803_close() {
    close(i2c_fd);
}

/*
 * vim: sw=4:et:ai
 */
