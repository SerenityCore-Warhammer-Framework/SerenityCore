/*
 * This file is part of the Serenity Warhammer Online Framework
 * 
 * Copyright (c)    : SerenityCore Project All rights reserved.
 * Webiste          : serenitycore.org
 * Wiki             : wiki.serenitycore.org
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
#ifndef SERENITY_DEFINES_HPP
#define SERENITY_DEFINES_HPP

#include "CompilerDefines.hpp"

#if SERENITY_COMPILER == SERENITY_COMPILER_GNU
#  if !defined(__STDC_FORMAT_MACROS)
#    define __STDC_FORMAT_MACROS
#  endif
#  if !defined(__STDC_CONSTANT_MACROS)
#    define __STDC_CONSTANT_MACROS
#  endif
#  if !defined(_GLIBCXX_USE_NANOSLEEP)
#    define _GLIBCXX_USE_NANOSLEEP
#  endif
#  if defined(HELGRIND)
#    include <valgrind/helgrind.h>
#    undef _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE
#    undef _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER
#    define _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(A) ANNOTATE_HAPPENS_BEFORE(A)
#    define _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(A)  ANNOTATE_HAPPENS_AFTER(A)
#  endif
#  if defined(VALGRIND)
#    include <valgrind/memcheck.h>
#  endif
#endif

#include <cstddef>
#include <cinttypes>
#include <climits>


#define SERENITY_LITTLEENDIAN 0
#define SERENITY_BIGENDIAN    1

#if !defined(SERENITY_ENDIAN)
#  if defined (BOOST_BIG_ENDIAN)
#    define SERENITY_ENDIAN SERENITY_BIGENDIAN
#  else
#    define SERENITY_ENDIAN SERENITY_LITTLEENDIAN
#  endif
#endif

#if SERENITY_PLATFORM == SERENITY_PLATFORM_WINDOWS
#  define SERENITY_PATH_MAX 260
#  define _USE_MATH_DEFINES
#  ifndef DECLSPEC_NORETURN
#    define DECLSPEC_NORETURN __declspec(noreturn)
#  endif //DECLSPEC_NORETURN
#  ifndef DECLSPEC_DEPRECATED
#    define DECLSPEC_DEPRECATED __declspec(deprecated)
#  endif //DECLSPEC_DEPRECATED
#else // SERENITY_PLATFORM != SERENITY_PLATFORM_WINDOWS
#  define SERENITY_PATH_MAX PATH_MAX
#  define DECLSPEC_NORETURN
#  define DECLSPEC_DEPRECATED
#endif // SERENITY_PLATFORM

#if SERENITY_COMPILER == SERENITY_COMPILER_GNU
#  define ATTR_NORETURN __attribute__((__noreturn__))
#  define ATTR_PRINTF(F, V) __attribute__ ((__format__ (__printf__, F, V)))
#  define ATTR_DEPRECATED __attribute__((__deprecated__))
#else //SERENITY_COMPILER != SERENITY_COMPILER_GNU
#  define ATTR_NORETURN
#  define ATTR_PRINTF(F, V)
#  define ATTR_DEPRECATED
#endif //SERENITY_COMPILER == SERENITY_COMPILER_GNU

#ifdef SERENITY_API_USE_DYNAMIC_LINKING
#  if SERENITY_COMPILER == SERENITY_COMPILER_MICROSOFT
#    define SC_API_EXPORT __declspec(dllexport)
#    define SC_API_IMPORT __declspec(dllimport)
#  elif SERENITY_COMPILER == SERENITY_COMPILER_GNU
#    define SC_API_EXPORT __attribute__((visibility("default")))
#    define SC_API_IMPORT
#  else
#    error compiler not supported!
#  endif
#else
#  define SC_API_EXPORT
#  define SC_API_IMPORT
#endif

#ifdef SERENITY_API_EXPORT_COMMON
#  define SC_COMMON_API SC_API_EXPORT
#else
#  define SC_COMMON_API SC_API_IMPORT
#endif

#ifdef SERENITY_API_EXPORT_PROTO
#  define SC_PROTO_API SC_API_EXPORT
#else
#  define SC_PROTO_API SC_API_IMPORT
#endif

#ifdef SERENITY_API_EXPORT_DATABASE
#  define SC_DATABASE_API SC_API_EXPORT
#else
#  define SC_DATABASE_API SC_API_IMPORT
#endif

#ifdef SERENITY_API_EXPORT_SHARED
#  define SC_SHARED_API SC_API_EXPORT
#else
#  define SC_SHARED_API SC_API_IMPORT
#endif

#ifdef SERENITY_API_EXPORT_GAME
#  define SC_GAME_API SC_API_EXPORT
#else
#  define SC_GAME_API SC_API_IMPORT
#endif

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;


#endif //SERENITY_DEFINES_HPP
