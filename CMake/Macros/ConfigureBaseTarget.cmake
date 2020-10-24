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

# >>> Eine INTERFACE Library, um das Ziel-COM für andere Ziele zur verfügung zu stellen.
add_library(serenity-compile-option-interface INTERFACE)

# Use -std=c++11 instead of -std=gnu++11
set(CXX_EXTENSIONS OFF)

# >>> Eine INTERFACE Library, um das target FEATURE für andere Ziele zu verfügung zu stellen.
add_library(serenity-feature-interface INTERFACE)
target_compile_features(serenity-feature-interface
        INTERFACE
        cxx_alias_templates
        cxx_auto_type
        cxx_constexpr
        cxx_decltype
        cxx_decltype_auto
        cxx_final
        cxx_lambdas
        cxx_generic_lambdas
        cxx_variadic_templates
        cxx_defaulted_functions
        cxx_nullptr
        cxx_trailing_return_types
        cxx_return_type_deduction)

# >>> Eine INTERFACE Library, um die Warning-Levels auf anderen Zielen zur verfügung zu stellen.
add_library(serenity-warning-interface INTERFACE)

# >>> Eine INTERFACE Library. für alle anderen INTERFACES
add_library(serenity-default-interface INTERFACE)
target_link_libraries(serenity-default-interface
        INTERFACE
        serenity-compile-option-interface
        serenity-feature-interface)

# >>> Eine INTERFACE Library, genutzt für alle silence warnungen
add_library(serenity-no-warning-interface INTERFACE)

# An interface library to change the default behaviour
# to hide symbols automatically.
add_library(serenity-hidden-symbols-interface INTERFACE)


# >>> Eine INTERFACE Verschmelzung
add_library(serenity-dependencies-interface INTERFACE)
target_link_libraries(serenity-dependencies-interface
        INTERFACE
        serenity-default-interface
        serenity-no-warning-interface
        serenity-hidden-symbols-interface)

# >>> Eine INTERFACE Library verschmelzung was sicherstellt,
# >>> das alle flags und definitionen in allen projekten vorhanden ist
add_library(serenity-core-interface INTERFACE)
target_link_libraries(serenity-core-interface
        INTERFACE
        serenity-default-interface
        serenity-warning-interface)