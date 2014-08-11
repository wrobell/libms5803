/*
 * libms5803 - MS5803 pressure sensor library
 *
 * Copyright (C) 2014 by Artur Wroblewski <wrobell@pld-linux.org>
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

/**
 * Initialize MS5803 sensor.
 *
 * Initialize I2C bus and calibrate MS5803 sensor.
 */
void ms5803_init();

/**
 * Read pressure and temperature from MS5803 sensor.
 */
int ms5803_read(int32_t *pressure, int32_t *temperature);

/**
 * Close MS5803 sensor.
 *
 * Close I2C bus access.
 */
void ms5803_close();

#endif /* _MS5803_H_ */

/*
 * vim: sw=4:et:ai
 */
