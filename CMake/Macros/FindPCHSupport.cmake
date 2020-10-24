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

if (CMAKE_VERSION VERSION_LESS "3.16.0")
  if (MSVC)
    # Specify the maximum PreCompiled Header memory allocation limit
    # Fixes a compiler-problem when using PCH - the /Ym flag is adjusted by the compiler in MSVC2012,
    # hence we need to set an upper limit with /Zm to avoid discrepancies)
    # (And yes, this is a verified, unresolved bug with MSVC... *sigh*)
    #
    # Note: This workaround was verified to be required on MSVC 2017 as well
    set(COTIRE_PCH_MEMORY_SCALING_FACTOR 500)
  endif ()

  include(cotire)

  function(ADD_CXX_PCH TARGET_NAME_LIST PCH_HEADER)
    # Use the header for every target
    foreach (TARGET_NAME ${TARGET_NAME_LIST})
      # Disable unity builds
      set_target_properties(${TARGET_NAME} PROPERTIES COTIRE_ADD_UNITY_BUILD OFF)

      # Set the prefix header
      set_target_properties(${TARGET_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${PCH_HEADER})

      # Workaround for cotire bug: https://github.com/sakra/cotire/issues/138
      set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 14)
    endforeach ()

    cotire(${TARGET_NAME_LIST})
  endfunction(ADD_CXX_PCH)
else()
  function(ADD_CXX_PCH TARGET_NAME_LIST PCH_HEADER)
    foreach(TARGET_NAME ${TARGET_NAME_LIST})
      target_precompile_headers(${TARGET_NAME} PRIVATE ${PCH_HEADER})
    endforeach()
  endfunction(ADD_CXX_PCH)
endif()