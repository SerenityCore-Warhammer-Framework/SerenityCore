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

# >>> Set the build-directive
target_compile_definitions(serenity-compiling-options-interface
        INTERFACE
            -D_BUILD_DIRECTIVE="$<CONFIG>"
        )
set(GCC_EXPECTED_VERSION 6.3.0)

# >>> Check for CXX Compiler version with GCC_EXPECTED_VERSION
if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS GXX_EXPECTED_VERSION)
    message(FATAL_ERROR "GCC: SerenityCore Warhammer Framework required version ${GCC_EXPECTED_VERSION} to build, but only found ${CMAKE_CXX_COMPILER_VERSION}")
endif()

# >>> Check for Build Platform
if(PLATFORM EQUAL 32)
    # Required on 32-Bit systems to enable SSE2
    target_compile_options(serenity-compiling-options-interface
            INTERFACE
                -msse2
                -mfpmath=sse)
endif()
target_compile_definitions(serenity-compiling-options-interface
        INTERFACE
            -DHAVE_SSE2
            -D__SSE2__)
message(STATUS "GCC: SFMT enabled, SSE2 flags forced")

if(WITH_WARNINGS)
    target_compile_options(serenity-warning-interface
            INTERFACE
                -W
                -Wall
                -Wextra
                -Winit-self
                -Winvalid-pch
                -Wfatal-errors
                -Woverloaded-virtual
                -Wno-deprecated-copy)

    message(STATUS "GCC: All warnings enabled")
endif()