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
#ifndef SERENITY_COMPILERDEFINES_HPP
#define SERENITY_COMPILERDEFINES_HPP

#define SERENITY_PLATFORM_WINDOWS   0
#define SERENITY_PLATFORM_UNIX      1

#if defined(_WIN64)
#   define SERENITY_PLATFORM SERENITY_PLATFORM_WINDOWS
#elif defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
#else
#   define SERENITY_PLATFORM SERENITY_PLATFORM_UNIX
#endif

#define SERENITY_COMPILER_MICROSOFT 0
#define SERENITY_COMPILER_GNU       1

#ifdef _MSC_VER
#   define SERENITY_COMPILER SERENITY_COMPILER_MICROSOFT
#elif defined(__GNUC__)
#   define SERENITY_COMPILER SERENITY_COMPILER_GNU
#   define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#   error "FATAL ERROR: Unknown Compiler."
#endif

#endif //SERENITY_COMPILERDEFINES_HPP
