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

# >>> An INTERFACE Library to make the compiling targets available to other targets
add_library(serenity-compiling-options-interface INTERFACE)

# >>> Use -std=c++11 instead of -std=gnu++11
set(CXX_EXTENSIONS OFF)

# >>> An INTERFACE Library to make the serenity-features INTERFACE available to other targets
add_library(serenity-feature-interface INTERFACE)
target_compile_features(serenity-feature-interface
        INTERFACE # A list of Compiling features that we will use.
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

# An INTERFACE Library to make warning levels available to other targets
add_library(serenity-warning-interface INTERFACE)


# An INTERFACE Library used for all other INTERFACES
add_library(serenity-default-interface INTERFACE)
target_link_libraries(serenity-default-interface
        INTERFACE # A list of INTERFACES that we will link into
        serenity-compiling-options-interface
        serenity-feature-interface)

# An INTERFACE Library for silencing all warnings
add_library(serenity-no-warning-interface INTERFACE)
target_compile_options(serenity-no-warning-interface
        INTERFACE
            -w)

# An INTERFACE Library to change the behaviour to hide symbols automatically
add_library(serenity-hidden-symbols-interface INTERFACE)


# An INTERFACE Library which provides the flags and definitions used by the dependencies targets
add_library(serenity-dependencies-interface INTERFACE)
target_link_libraries(serenity-dependencies-interface
        INTERFACE
        serenity-default-interface          # Provides "Compiling" and "Feature" Interface Libraries
        serenity-no-warning-interface       # Silencing all warnings
        serenity-hidden-symbols-interface   # Default behaviour (hide symbols)
        )

# An INTERFACE Library which provides the flags and definitions are used by the core
add_library(serenity-core-interface INTERFACE)
target_link_libraries(serenity-core-interface
        INTERFACE
        serenity-default-interface
        serenity-warning-interface
        )