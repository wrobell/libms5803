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

import cffi

ffi = cffi.FFI()
ffi.cdef("""
int ms5803_init(const char *, unsigned char);
int ms5803_read(int32_t *, int32_t *);
int ms5803_close();
""")

ffi.set_source('_ms5803', '')

# vim: sw=4:et:ai
