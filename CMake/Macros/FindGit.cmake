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

set(_REQUIRED_GIT_VERSION "1.7")

find_program(GIT_EXECUTABLE
  NAMES
    git git.cmd
  HINTS
    ENV PATH
  DOC "Full path to git commandline client"
)
MARK_AS_ADVANCED(GIT_EXECUTABLE)

if(NOT GIT_EXECUTABLE)
  message(FATAL_ERROR "
    Git was NOT FOUND on your system - did you forget to install a recent version, or setting the path to it?
    Observe that for revision hash/date to work you need at least version ${_REQUIRED_GIT_VERSION}")
else()
  message(STATUS "Found git binary : ${GIT_EXECUTABLE}")
  execute_process(
    COMMAND "${GIT_EXECUTABLE}" --version
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    OUTPUT_VARIABLE _GIT_VERSION
    ERROR_QUIET
  )
endif()
