/*
 * This file is part of the Serenity Warhammer Online Framework
 *
 * See LICENSE file for more information
 *
 * Website: serenitycore.org
 * Wiki: wiki.serenitycore.org
 * Git: github.com/SerenityCore-Warhammer-Framework
 *
 * License:
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SERENITY_FRAMEWORK_HPP
#define SERENITY_FRAMEWORK_HPP

#include "Defines.hpp"
#include <array>
#include <memory>
#include <string>
#include <utility>

#if SERENITY_PLATFORM == SERENITY_PLATFORM_WINDOWS
#  if SERENITY_COMPILER == SERENITY_COMPILER_INTEL
#    if !defined(BOOST_ASIO_HAS_MOVE)
#      define BOOST_ASIO_HAS_MOVE
#    endif // !defined(BOOST_ASIO_HAS_MOVE)
#  endif // if SERENITY_COMPILER == SERENITY_COMPILER_INTEL
#else
#  include <sys/types.h>
#  include <sys/ioctl.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <unistd.h>
#  include <netdb.h>
#  include <cstdlib>
#endif

#define stricmp strcasecmp
#define strnicmp strncasecmp

inline unsigned long atoul(char const* str) { return strtoul(str, nullptr, 10); }
inline unsigned long long atoull(char const* str) { return strtoull(str, nullptr, 10); }

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif

#define MAX_QUERY_LEN 32*1024



#endif //SERENITY_FRAMEWORK_HPP
