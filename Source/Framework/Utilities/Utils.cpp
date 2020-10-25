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

// >>> SerenityCore Framework Includes
#include "Utils.hpp"
#include "Framework.hpp"

// >>> C/CXX Standard Includes
#include <algorithm>
#include <sstream>
#include <cstdarg>
#include <ctime>
#include <cstring>
// Unix includes
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



Tokenizer::Tokenizer(const std::string &src, const char seperator, uint32 vectorReserve, bool KeepEmptyStrings) {

    // Initialize m_str with a new char with the size of the source string
    m_str = new char[src.length() + 1];
    // Copy the src string with length into the new m_str char
    memcpy(m_str, src.c_str(), src.length() + 1);

    if(vectorReserve) {
        m_Storage.reserve(vectorReserve);
    }

    char* PosOld = m_str;
    char* PosNew = m_str;

    for(;;) {
        if(*PosNew == seperator) {
            if(KeepEmptyStrings || PosOld != PosNew)
                m_Storage.push_back(PosOld);

            PosOld = PosNew + 1;
            *PosNew = '\0';
        } else if(*PosNew == '\0') {
            if(PosOld != PosNew)
                m_Storage.push_back(PosOld);

            break;
        }

        ++PosNew;
    }
}