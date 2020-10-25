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
#ifndef SERENITY_UTILS_HPP
#define SERENITY_UTILS_HPP

// >>> SerenityCore Framework Includes
#include "Defines.hpp"
#include "Errors.hpp"

// >>> C/CXX Standard Includes
#include <array>
#include <string>
#include <vector>

class SC_FRAMEWORK_API Tokenizer {
public:
    typedef std::vector<char const*> StorageType;

    typedef StorageType::size_type sizeType;
    typedef StorageType::const_iterator const_iterator;
    typedef StorageType::reference reference;
    typedef StorageType::const_reference const_reference;

public:
    Tokenizer(const std::string &src, char const seperator, uint32 vectorReserve = 0,
              bool KeepEmptyStrings = true);
    ~Tokenizer() { delete[] m_str; }

    const_iterator begin() const { return m_Storage.begin(); }
    const_iterator end() const { return m_Storage.end(); }

    sizeType size() const { return m_Storage.size(); }

    reference operator[] (sizeType i) { return m_Storage[i]; }
    const_reference  operator[] (sizeType i) const { return m_Storage[i]; }

private:
    char* m_str;
    StorageType m_Storage;
};


#endif //SERENITY_UTILS_HPP
