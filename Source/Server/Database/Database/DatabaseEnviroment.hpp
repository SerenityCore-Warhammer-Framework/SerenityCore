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
#ifndef SERENITY_DATABASEENVIROMENT_HPP
#define SERENITY_DATABASEENVIROMENT_HPP

#include "Defines.hpp"
#include "DatabaseWorkerPool.hpp"

#include "Implementation/LoginDatabase.hpp"
#include "Implementation/CharacterDatabase.hpp"
#include "Implementation/WorldDatabase.hpp"
#include "Implementation/HotfixDatabase.hpp"

#include "Field.hpp"
#include "PreparedStatement.hpp"
#include "QueryCallback.hpp"
#include "QueryResult.hpp"
#include "Transaction.hpp"

SC_DATABASE_API extern DatabaseWorkerPool<LoginDatabaseConnection> LoginDatabase;
SC_DATABASE_API extern DatabaseWorkerPool<CharacterDatabaseConnection> CharacterDatabase;
SC_DATABASE_API extern DatabaseWorkerPool<WorldDatabaseConnection> WorldDatabase;
SC_DATABASE_API extern DatabaseWorkerPool<HotfixDatabaseConnection> HotfixDatabase;


#endif //SERENITY_DATABASEENVIROMENT_HPP
