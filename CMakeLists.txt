#
# This file is part of the Serenity Warhammer Online Framework
# 
# Copyright (c)    : SerenityCore Project All rights reserved.
# Webiste          : serenitycore.org
# Wiki             : wiki.serenitycore.org
#
# License:
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along
# with this program. If not, see <http://www.gnu.org/licenses/>.

# >>> Wir brauchen mindestens CMake > 3.16.3
cmake_minimum_required(VERSION 3.16.3)

# >>> Setze Projekt Name
project(serenity)

# >>> Füge CMake Macros in die liste ein
list(APPEND CMAKE_MODULE_PATH
        "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Macros")

# >>> Für einen schnelleren compiling prozess wenn die CMake-Version < 3.16.0 ist
if(CMAKE_VERSION VERSION_LESS "3.16.0")
    list(APPEND CMAKE_MODULE_PATH
            "${CMAKE_SOURCE_DIR}/Dependencies/Cotire")
endif()

include(CheckCXXSourceRuns)
include(CheckIncludeFiles)
include(ConfigureBaseTarget)
include(CheckPlatform)

# >>> Finde Packete - Libraries die wir brauchen
find_package(MySQL)
find_package(Git)
find_package(PCHSupport)
find_package(OpenSSL)
find_package(Boost)

# >>> Include CMake Scripts
include(GroupSources)
include(AutoCollect)

add_subdirectory(Dependencies)

add_subdirectory(Source)