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

#include <iostream>

#include "DatabaseLoader.hpp"

DatabaseLoader::DatabaseLoader(std::string const& logger, uint32 const defaultUpdateMask) :
            m_Logger(logger), m_AutoSetup(false), m_UpdateFlags(defaultUpdateMask) {

}

bool DatabaseLoader::Load() {
    if(!m_UpdateFlags)
        std::cout << "Automatic updates are disabled" << std::endl;
    if(!OpenDatabases())
        return false;
    if(!PopulateDatabases())
        return false;
    if(!UpdateDatabases())
        return false;
    if(!PrepareStatements())
        return false;

    return true;
}

bool DatabaseLoader::OpenDatabases() {
    return Process(m_Open);
}
bool DatabaseLoader::PopulateDatabases() {
    return Process(m_Populate);
}
bool DatabaseLoader::UpdateDatabases() {
    return Process(m_Update);
}
bool DatabaseLoader::PrepareStatements() {
    return Process(m_Prepare);
}

bool DatabaseLoader::Process(std::queue<Predicate> &queue) {
    while (!queue.empty()) {
        if(!queue.front()()) {
            while (!m_Close.empty()) {
                m_Close.top()();
                m_Close.pop();
            }
            return false;
        }
        queue.pop();
    }
    return true;
}