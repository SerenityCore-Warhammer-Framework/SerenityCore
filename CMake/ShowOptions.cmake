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

message("")
message(">>> SerenityCore Warhammer Online Framework Revision   : ${RevHash} ${RevDate} (${RevBranch} branch)")
message(">>> SerenityCore Warhammer Online Framework BuildType  : ${CMAKE_BUILD_TYPE}")
message("")
message(">>> Install Core to...                                 : ${CMAKE_INSTALL_PREFIX}")
message(">>> Install Libraries to...                            : ${LIBSDIR}")
message(">>> Install Configuration to...                        : ${CONF_DIR}")
message("")
if(SERVERS)
    message(">>> Build World/Authserver                             : Yes (default)")
else()
    message(">>> Build World/Authserver                             : No")
endif()
message("")

if(USE_COREPCH)
    message(">>> Build Core with PCH                                : Yes (default)")
else()
    message(">>> Build Core with PCH                                : No")
endif()
message("")