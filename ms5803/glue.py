#
# libms5803 - MS5803 pressure sensor library
#
# Copyright (C) 2014-2016 by Artur Wroblewski <wrobell@pld-linux.org>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

from _ms5803 import ffi

class Sensor(object):
    """
    MS5803 sensor communication interface.
    """
    def __init__(self, f_dev, address):
        """
        Initialize pressure sensor and read its calibration coefficients.

        :param f_dev: I2C device filename, i.e. /dev/i2c-0.
        :param address: I2C device address, i.e. 0x77.
        """
        self._lib = ffi.dlopen('libms5803.so.0')
        self._lib.ms5803_init(f_dev, address)
        self._p_value = ffi.new('int32_t *')
        self._t_value = ffi.new('int32_t *')


    def read(self):
        """
        Read pressure and temperature from sensor.
        """
        px = self._p_value
        tx = self._t_value
        self._lib.ms5803_read(px, tx)
        return px[0], tx[0]


# vim: sw=4:et:ai
