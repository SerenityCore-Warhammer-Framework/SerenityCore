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

# >>> First Collect all Source Files
CollectIncludeDirectories(
        ${CMAKE_CURRENT_SOURCE_DIR}                     # The Directory where located the sources
        PRIVATE_SOURCES                                 # The Variable Name of the Private Sources
                                                        # Excludes
        ${CMAKE_CURRENT_SOURCE_DIR}/Debugging
        ${CMAKE_CURRENT_SOURCE_DIR}/Platform
        ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders)

# >>> Manually set sources for Debugging directory
list(APPEND PRIVATE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Debugging/Errors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Debugging/Errors.hpp)

if(USE_COREPCH)
    set(PRIVATE_PCH_HEADER PrecompiledHeaders/FrameworkPCH.hpp)
endif()


GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(-DSERENITY_API_EXPORT_FRAMEWORK)

add_library(Framework
        ${PRIVATE_SOURCES})


# >>> DO NOT ADD ANY EXTRA INCLUDE DIRECTORIES HERE!!! <<<
# As we don`t want the Framework Library to depend on anything else than SerenityCore(SC) dependencies, and itself.
# This way we ensure that if either a pr dies that without modifying this file, a compile error will be generated,
# either this file will be modified so it is detected more easily.
# While it is OK to include files from other libs as long as they don`t require linkage (enums, defines ...)
# it is discouraged to do so unless necessary, as it will pullout include_directories leading to further
# unnoticed dependency
# Linker Dependency requirements: none
CollectIncludeDirectories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC_INCLUDES
        # Exclude
        ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders)

target_include_directories(Framework
        PUBLIC
            # Provide the binary dir for all child targets
            ${CMAKE_BINARY_DIR}
            ${PUBLIC_INCLUDES}
        PRIVATE
            ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(Framework
        PRIVATE
            process
            serenity-core-interface
        PUBLIC
            boost
            fmt
            g3dlib
            Detour
            sfmt
            utf8cpp
            openssl
            valgrind
            threads
            jemalloc)

add_dependencies(Framework RevisionData.hpp)

set_target_properties(Framework
        PROPERTIES
            FOLDER
                "Server")

if (USE_COREPCH)
    add_cxx_pch(Framework ${PRIVATE_PCH_HEADER})
endif ()