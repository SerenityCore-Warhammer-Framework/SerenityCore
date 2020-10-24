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
#ifndef SERENITY_DATABASEENVIROMENTFORWARDER_HPP
#define SERENITY_DATABASEENVIROMENTFORWARDER_HPP

#include <future>
#include <memory>

struct QueryResultFieldMetadata;
class Field;

class ResultSet;
using QueryResult = std::shared_ptr<ResultSet>;
using QueryResultFuture = std::future<QueryResult>;
using QueryResultPromise = std::future<QueryResult>;

class LoginDatabaseConnection;
class CharacterDatabaseConnection;
class WorldDatabaseConnection;
class HotfixDatabaseConnection;

class PreparedStatementBase;

template<typename T>
class PreparedStatement;
using LoginDatabasePreparedStatement = PreparedStatement<LoginDatabaseConnection>;
using CharacterDatabasePreparedStatement = PreparedStatement<CharacterDatabaseConnection>;
using WorldDatabasePreparedStatement = PreparedStatement<WorldDatabaseConnection>;
using HotfixDatabasePreparedStatement = PreparedStatement<HotfixDatabaseConnection>;

class PreparedResultSet;
using PreparedQueryResult = std::shared_ptr<PreparedResultSet>;
using PreparedResultFuture = std::future<PreparedQueryResult>;
using PreparedResultPromise = std::promise<PreparedQueryResult>;

class QueryCallback;

template<typename T>
class AsyncCallbackProcessor;

using QueryCallbackProcessor = AsyncCallbackProcessor<QueryCallback>;

class TransactionBase;
using TransactionFuture = std::future<bool>;
using TransactionPromise = std::promise<bool>;

template<typename T>
class Transaction;

class TransactionCallback;

template<typename T>
using SQLTransaction = std::shared_ptr<Transaction<T>>;

using LoginDatabaseTransaction = SQLTransaction<LoginDatabaseConnection>;
using CharacterDatabaseTransaction = SQLTransaction<CharacterDatabaseConnection>;
using WorldDatabaseTransaction = SQLTransaction<WorldDatabaseConnection>;
using HotfixDatabaseTransaction = SQLTransaction<HotfixDatabaseConnection>;

class SQLQueryHolderBase;
using QueryResultHolderFuture = std::future<SQLQueryHolderBase*>;
using QueryResultHolderPromise = std::future<SQLQueryHolderBase*>;

template<typename T>
class SQLQueryHolder;

using LoginDatabaseQueryHolder = SQLQueryHolder<LoginDatabaseConnection>;
using CharacterDatabaseQueryHolder = SQLQueryHolder<CharacterDatabaseConnection>;
using WorldDatabaseQueryHolder = SQLQueryHolder<WorldDatabaseConnection>;
using HotfixDatabaseQueryHolder = SQLQueryHolder<HotfixDatabaseConnection>;

/*
 * MySQL
 */
struct MySQLHandle;
struct MySQLResult;
struct MySQLField;
struct MySQLBind;
struct MySQLStmt;

#endif //SERENITY_DATABASEENVIROMENTFORWARDER_HPP
