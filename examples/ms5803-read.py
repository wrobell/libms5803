#
# libms5803 - MS5803 pressure sensor library
#
# Copyright (C) 2014 by Artur Wroblewski <wrobell@pld-linux.org>
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

import argparse
import time
from datetime import datetime
from functools import partial

import ms5803

parser = argparse.ArgumentParser(description='MS5803 pressure sensor example')
parser.add_argument('device', help='I2C device filename, i.e. /dev/i2c-0')
parser.add_argument(
    'address', type=partial(int, base=16),
    help='I2C device address, i.e. 0x77 (hex value)'
)
args = parser.parse_args()

sensor = ms5803.Sensor(args.device, args.address)
while True:
    pressure, temp = sensor.read()
    print('{}: {}bar {}C'.format(datetime.now(), pressure / 10000, temp / 100))

    time.sleep(0.5)

# vim: sw=4:et:ai
