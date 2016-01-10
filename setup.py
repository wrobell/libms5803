#!/usr/bin/env python
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

from setuptools import setup, find_packages

import ms5803.glue_build

setup(
    name='ms5803',
    packages=find_packages('.'),
#    ext_modules=[ms5803.glue_build.ffi.distutils_extension()],
    setup_requires=['cffi >= 1.4.2'],
    cffi_modules=['ms5803/glue_build.py:ffi'],
    install_requires=['cffi >= 1.4.2'],
    version='0.2.0',
    description='libms5803 - MS5803 pressure sensor library',
    author='Artur Wroblewski',
    author_email='wrobell@pld-linux.org',
    url='https://github.com/wrobell/libms5803',
    classifiers=[
        'Topic :: Software Development :: Libraries',
        'License :: OSI Approved :: GNU General Public License v3 or later (GPLv3+)',
        'Programming Language :: Python :: 3',
        'Development Status :: 4 - Beta',
    ],
    license='GPLv3+'
)

# vim: sw=4:et:ai
