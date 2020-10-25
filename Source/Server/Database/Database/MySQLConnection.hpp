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

#ifndef SERENITY_SERVER_DATABASE
#define SERENITY_SERVER_DATABASE

// >>> Serenity Framework Includes
#include "Defines.hpp"
#include "DatabaseEnviromentForwarder.hpp"

// >>> C/CXX Standard Includes
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

template<typename T>
class ProducerConsumerQueue;

//class DatabaseWorkerPool;
class MySQLPreparedStatement;
class SQLOperation;

/**
 * MySQL Connection Flags enumeration
 * To handle easy type of the connection type.
 */
enum SC_DATABASE_API eConnectionFlags {

    // MySQL Connection Flag for asynchronous connections.
    CONNECTION_ASYNC = 0x1,

    // MySQL Connection Flag for synchronous connections.
    CONNECTION_SYNCH = 0x2,

    // Connection Flag to use both connection Flag types.
    CONNECTION_BOTH = CONNECTION_ASYNC | CONNECTION_SYNCH
};

/**
 *
 */
struct SC_DATABASE_API MySQLConnectionInfo {
    explicit MySQLConnectionInfo(std::string const& infoString);

    std::string User;
    std::string Password;
    std::string Database;
    std::string Host;
    std::string PortOrtSocket;
};

class SC_DATABASE_API MySQLConnection {
    //template<class T> friend class DatabaseWorkerPool;
    friend class PingOperation;

public:
    // Constructor for Synchronous MySQL Connections.
    MySQLConnection(MySQLConnectionInfo& connectionInfo);

    // Constructor for Asynchronous MySQL Connections.
    MySQLConnection(ProducerConsumerQueue<SQLOperation*>* queue, MySQLConnectionInfo& connectionInfo);

    virtual ~MySQLConnection();

    // To open a MySQL Connection.
    virtual uint32 Open();

    // To close a MySQL Connection.
    void Close();

    // To execute a SQL Statement.
    bool Execute(char const* sql);
    // To Execute a Prepared SQL Statement
    bool Execute(PreparedStatementBase* statement);

    ResultSet* Query(char const* sql);
    PreparedResultSet* Query(PreparedStatementBase* statement);

    bool _Query(char const* sql, MySQLResult** pResult, MySQLField** pFields, uint64* pRowCount, uint32* pFieldCount);
    bool _Query(PreparedStatementBase* statement, MySQLResult** pResult, uint64* pRowCount, uint32* pFieldCount);

    void BeginTransaction();
    void RollbackTransaction();
    void CommitTransaction();
    int ExecuteTransaction(std::shared_ptr<TransactionBase> transaction);
    size_t EscapeString(char* to, const char* from, size_t length);
    void Ping();

    uint32 GetLastError();

protected:
    /*
     * Tries to acquire lock.
     * If lock is acquired by another thread the calling parent
     * will try another connection.
     */
    bool LockIfReady();

    /*
     * Called by parent database pool. will let other threads access this connection
     */
    void Unlock();

    uint32 GetServerVersion() const;
    MySQLPreparedStatement* GetPreparedStatement(uint32 index);
    void PreparedStatement(uint32 index, std::string const& sql, eConnectionFlags flags);

    //virtual void DoPrepareStatement() = 0;

    typedef std::vector<std::unique_ptr<MySQLPreparedStatement>> PreparedStatementContainer;

    // Container for the prepared MySQL Statements;
    PreparedStatementContainer m_Statements;

    // When we will reconnecting
    bool m_bReconnecting;

    // When there an error while preparing statements
    bool m_bPrepareError;

private:
    bool m_HandleMySQLErrorNo(uint32 errorNo, uint8 attempts = 5);

    ProducerConsumerQueue<SQLOperation*>* m_Queue;
    //std::unique_ptr<DatabaseWorkerPool> m_Worker;
    MySQLHandle* m_Mysql;
    MySQLConnectionInfo& m_ConnectionInfo;
    eConnectionFlags m_ConnectionFlags;
    std::mutex m_Mutex;

    MySQLConnection(MySQLConnection const& right) = delete;
    MySQLConnection& operator = (MySQLConnection const& right) = delete;

};


#endif //SERENITY_SERVER_DATABASE