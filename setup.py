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

setup(
    name='ms5803',
    packages=find_packages('.'),
    version='0.1.0',
    description='libms5803 - MS5803 pressure sensor library',
    author='Artur Wroblewski',
    author_email='wrobell@pld-linux.org',
    url='https://github.com/wrobell/libms5803',
    setup_requires = ['setuptools_git >= 1.0'],
    classifiers=[
        'Topic :: Software Development :: Libraries',
        'Topic :: Scientific/Engineering :: GIS',
        'License :: OSI Approved :: GNU General Public License v3 or later (GPLv3+)',
        'Programming Language :: Python :: 3',
        'Development Status :: 4 - Beta',
    ],
    license='GPLv3+'
)

# vim: sw=4:et:ai
