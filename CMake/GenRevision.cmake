#
# This file is part of the Serenity Warhammer Online Framework
#
# See LICENSE file for more information
#
# Website: serenitycore.org
# Wiki: wiki.serenitycore.org
# Git: github.com/SerenityCore-Warhammer-Framework
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

if (NOT BUILDDIR)
    set(BUILDDIR ${CMAKE_BINARY_DIR})
endif ()

if (WITHOUT_GIT)
    set(RevDate "1991-8-12 00:00:00 +0000")
    set(RevHash "Unknown")
    set(RevBranch "Archived")
else()
    if (GIT_EXECUTABLE)
        # Create a revision-string that we can use
        execute_process(
                COMMAND "${GIT_EXECUTABLE}" describe --long --match init --dirty=+ --abbrev=12
                WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
                OUTPUT_VARIABLE RevInfo
                OUTPUT_STRIP_TRAILING_WHITESPACE
                ERROR_QUIET
        )

        # And grab the commits timestamp
        execute_process(
                COMMAND "${GIT_EXECUTABLE}" show -s --format=%ci
                WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
                OUTPUT_VARIABLE RevDate
                OUTPUT_STRIP_TRAILING_WHITESPACE
                ERROR_QUIET
        )

        # Also retrieve branch name
        execute_process(
                COMMAND "${GIT_EXECUTABLE}" rev-parse --abbrev-ref HEAD
                WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
                OUTPUT_VARIABLE RevBranch
                OUTPUT_STRIP_TRAILING_WHITESPACE
                ERROR_QUIET
        )
    endif ()

    if (NOT RevInfo)
        message(STATUS "
        Could not find a proper repository signature (hash) - you may need to pull tags with git fetch -t
        Continuing anyway - note that the versionstring will be set to \"Unknown 1991-08-12 00:00:00 (Archived)\"")
        set(RevDate "1991-08-12")
        set(RevHash "Unknown")
        set(RevBranch "Archived")
    else()
        string(REGEX REPLACE init-|[0-9]+-g "" RevHash ${RevInfo})
    endif ()
endif ()

if (NOT "${RevHash_cached}" MATCHES "${RevHash}" OR NOT "${RevBranch_cached}" MATCHES "${RevBranch}" OR NOT EXISTS "${BUILDDIR}/RevisionData.hpp")
    configure_file(
            "${CMAKE_SOURCE_DIR}/RevisionData.hpp.in.cmake"
            "${BUILDDIR}/RevisionData.hpp"
            @ONLY)
    set(RevHash_cached "${RevHash}" CACHE INTERNAL "Cached commit-hash")
    set(RevBranch_cached "${RevBranch}" CACHE INTERNAL "Cached branch name")
endif ()