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

#ifndef SERENITY_DATABASELOADER_HPP
#define SERENITY_DATABASELOADER_HPP

#include "Defines.hpp"

#include <functional>
#include <queue>
#include <stack>

class SC_DATABASE_API DatabaseLoader {
    DatabaseLoader(std::string const& logger, uint32 const defaultUpdateMask);

    bool Load();

    enum eDatabaseTypeFlag {
        DATABASE_NONE       =  0,

        DATABASE_LOGIN      =  1,
        DATABASE_CHARACTER  =  2,
        DATABASE_WORLD      =  3,

        DATABASE_HOTFIX     = 10,

        DATABASE_MASK_ALL = DATABASE_LOGIN | DATABASE_CHARACTER | DATABASE_WORLD | DATABASE_HOTFIX
    };

private:
    bool OpenDatabases();
    bool PopulateDatabases();
    bool UpdateDatabases();
    bool PrepareStatements();

    using Predicate = std::function<bool()>;
    using Closer = std::function<void()>;

    bool Process(std::queue<Predicate>& queue);

    std::string const m_Logger;
    bool const m_AutoSetup;
    uint32 const m_UpdateFlags;

    std::queue<Predicate> m_Open, m_Populate, m_Update, m_Prepare;
    std::stack<Closer> m_Close;
};


#endif //SERENITY_DATABASELOADER_HPP
