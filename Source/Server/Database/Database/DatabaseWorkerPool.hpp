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
#ifndef SERENITY_DATABASEWORKERPOOL_HPP
#define SERENITY_DATABASEWORKERPOOL_HPP

#include "Defines.hpp"
#include "DatabaseEnviromentForwarder.hpp"
#include "StringFormat.hpp"

#include <array>
#include <string>
#include <vector>

template<typename T>
class ProducerConsumerQueue;

class SQLOperation;
struct MySQLConnectionInfo;

template<class T>
class DatabaseWorkerPool {
private:
    enum eInternalIndex {
        IDX_ASYNC,
        IDX_SYNCH,
        IDX_SIZE
    };

public:
    DatabaseWorkerPool();
    ~DatabaseWorkerPool();

    void SetConnectionInfo(std::string const& infoString, uint8 const asyncThreads, uint8 const synchThreads);

    uint32 Open();
    void Close();

    bool PrepareStatements();

    inline MySQLConnectionInfo const* GetConnectionInfo() const { return m_ConnectionInfo.get(); }


    /*
     * Enqueues a one-way SQL operation in string format that will be executed asynchronously.
     * This method should only be used for queries that are only executed once, e.g during startup.
     */
    void Execute(char const* sql);

    /*
     * Enqueues a one-way SQL operation in string format -with variable args- that will be executed asynchronously.
     * This method should only be used for queries that are only executed once, e.g during startup.
     */
    template<typename Format, typename... Args>
    void PExecute(Format&& sql, Args&&... args) {
        if(Serenity::IsFormatEmptyOrNull(sql))
            return;

        Execute(Serenity::StringFormat(std::forward<Format>(sql), std::forward<Args>(args)...).c_str());
    }

    /*
     * Enqueues a one-way SQL operation in prepared statement format that will be executed asynchronously.
     * Statement must be prepared with CONNECTION_ASYNC flag.
     */
    void Execute(PreparedStatement<T>* statement);

    // >>> Direct Synchronous ONE-WAY statement methods. <<< //

    /*
     * Directly executes a one-way SQL operation in string format, that will block the calling thread,
     * until finished. This method should only be used for queries that are only executed once, e.g during startup.
     */
    void DirectExecute(char const* sql);

    /*
     * Directly executes a one-way SQL operation in string format -with variable args-,
     * that will block the calling thread until finished.
     * This method should only be used for queries that are only executed once, e.g during startup.
     */
    template<typename Format, typename... Args>
    void DirectPExecute(Format&& sql, Args&&... args) {}

    /*
     * Directly executes a one-way SQL operation in prepared statement format, that will block the calling thread until finished.
     * Statement must be prepared with the CONNECTION_SYNCH flag.
     */
    void DirectExecute(PreparedStatement<T>* statement);


    // >>> Synchronous Query (with resultset) methods. <<< //

    /*
     * Directly executes an SQL query in string format that will block the calling thread until finished.
     * Returns reference counted auto pointer, no need for manual memory management in upper level code.
     */
    QueryResult Query(char const* sql, T* connection = nullptr);

    /*
     * Directly executes an SQL query in string format -with variable args- that will block the calling thread until finished.
     * Returns reference counted auto pointer, no need for manual memory management in upper level code.
     */
    template<typename Format, typename... Args>
    QueryResult PQuery(Format&& sql, T* connection, Args&&... args) {
        if(Serenity::IsFormatEmptyOrNull(sql))
            return QueryResult(nullptr);

        return Query(Serenity::StringFormat(std::forward<Format>(sql), std::forward<Args>(args)...).c_str(), connection);
    }



private:
    uint32 OpenConnections(eInternalIndex type, uint8 numConnections);

    unsigned long EscapeString(char* to, char const* from, unsigned long length);

    void Enqueue(SQLOperation* op);

    /*
     * Gets a free connection in the synchronous connection pool.
     * Caller MUST call t->Unlock() after touching the MySQL context to prevent deadlocks.
     */
    T* GetFreeConnection();

    char const* GetDatabaseName() const;

    std::unique_ptr<ProducerConsumerQueue<SQLOperation*>> m_Queue;
    std::array<std::vector<std::unique_ptr<T>>, IDX_SIZE> m_Connections;
    std::unique_ptr<MySQLConnectionInfo> m_ConnectionInfo;
    std::vector<uint8> m_PreparedStatementSize;
    uint8 m_AsyncThreads, m_SynchThreads;


};


#endif //SERENITY_DATABASEWORKERPOOL_HPP
