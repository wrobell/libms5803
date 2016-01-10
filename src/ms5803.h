/*
 * libms5803 - MS5803 pressure sensor library
 *
 * Copyright (C) 2014-2016 by Artur Wroblewski <wrobell@pld-linux.org>
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

#if !defined (_MS5803_H_)
#define _MS5803_H_

/*!
 * \brief Initialize MS5803 sensor.
 *
 * I2C bus is initialized and sensor calibration coefficients are read.
 *
 * \param f_dev I2C device filename, i.e. /dev/i2c-0.
 * \param address I2C device address, i.e. 0x77.
 */
int ms5803_init(const char *f_dev, unsigned char address);

/*!
 * \brief Read pressure and temperature from MS5803 sensor.
 *
 * \param pressure Pressure - 1/10000 of bar or 1/10 of millibar.
 * \param temperature Temperature - 1/100 of Celsius.
 */
int ms5803_read(int32_t *pressure, int32_t *temperature);

/*!
 * \brief Release MS5803 sensor resources.
 *
 * Access to the I2C bus is closed.
 */
int ms5803_close();

#endif /* _MS5803_H_ */

/*
 * vim: sw=4:et:ai
 */
