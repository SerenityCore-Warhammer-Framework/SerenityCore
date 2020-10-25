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

CollectSourceFiles(
        ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE_SOURCES
        # Exclude
        ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders)

if (USE_COREPCH)
    set(PRIVATE_PCH_HEADER PrecompiledHeaders/DatabasePCH.hpp)
endif ()

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_library(Database
        ${PRIVATE_SOURCES})


# Do NOT add any extra include directory unless it does not create unneeded extra dependencies,
# and specially, not add any dependency to neither of these: shared, game, scripts
# This way we ensure that if either a PR does that without modifying this file,
# a compile error will be generated, either this file will be modified so it
# is detected more easily.
# While it is OK to include files from other libs as long as they don't require
# linkage (enums, defines...) it is discouraged to do so unless necessary, as it will pullute
# include_directories leading to further unnoticed dependency aditions
# Linker Depencency requirements: Framework

CollectIncludeDirectories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC_INCLUDES
        # Exclude
        ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders)

target_include_directories(Database
        PUBLIC
            ${PUBLIC_INCLUDES}
        PRIVATE
            ${CMAKE_CURRENT_BINARY_DIR})

add_definitions(-DSERENITY_API_EXPORT_DATABASE)

target_link_libraries(Database
        PRIVATE
            serenity-core-interface
            mysql
            Framework
        PUBLIC
            Framework)

set_target_properties(Database
        PROPERTIES
            FOLDER
                "Server")

if (USE_COREPCH)
    add_cxx_pch(Database ${PRIVATE_PCH_HEADER})
endif ()