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

#include "Defines.hpp"
#include "MySQLConnection.hpp"
#include "Framework.hpp"
#include "DatabaseWorker.hpp"
#include "MySQLHacks.hpp"
#include "MySQLPreparedStatement.hpp"
#include "PreparedStatement.hpp"
#include "QueryResult.hpp"
#include "Transaction.hpp"
#include "MySQLWorkaround.hpp"
#include "Utils.hpp"

#include <errmsg.h>
#include <mysqld_error.h>

MySQLConnectionInfo::MySQLConnectionInfo(const std::string &infoString) {
    Tokenizer tokenizer(infoString, ';');

    std::string DefaultString;
    DefaultString = "127.0.0.1;3306;serenity;serenity;accounts";
    // when the infostring not contains 5 sectors return
    if(tokenizer.size() != 5) {
        printf("infoString is not in the right format %s", DefaultString.c_str());
        return;
    }

    // When the infostring is okay... assign the tokens...
    uint8 i = 0;

    Host.assign(tokenizer[i++]);
    PortOrtSocket.assign(tokenizer[i++]);
    User.assign(tokenizer[i++]);
    Password.assign(tokenizer[i++]);
    Database.assign(tokenizer[i++]);
}

/**
 * Open the MySQL Connection with the given infoString
 * @param connectionInfo The Connection String
 */
MySQLConnection::MySQLConnection(MySQLConnectionInfo &connectionInfo) :
    m_bReconnecting(false),
    m_bPrepareError(false),
    m_Queue(nullptr),
    m_Mysql(nullptr),
    m_ConnectionInfo(connectionInfo),
    m_ConnectionFlags(CONNECTION_SYNCH) {

}
/**
 * Deconstructor
 * Closed the MySQL Connection rightly
 */
MySQLConnection::~MySQLConnection() {
    Close();
}

/**
 * Open a MySQL Connection
 */
uint32 MySQLConnection::Open() {
    MYSQL *mysqlInit;
    mysqlInit = mysql_init(nullptr);
    if(!mysqlInit) {
        printf("MySQL Error: Could not initialize MySQL Connection to Database `%s`", m_ConnectionInfo.Database.c_str());
        return CR_UNKNOWN_ERROR;
    }

    int port;
    char const* unixSocket;

    mysql_options(mysqlInit, MYSQL_SET_CHARSET_NAME, "utf8");

    if(m_ConnectionInfo.Host == ".") {
        unsigned int opt = MYSQL_PROTOCOL_SOCKET;
        mysql_options(mysqlInit, MYSQL_OPT_PROTOCOL, (char const*)&opt);
        m_ConnectionInfo.Host = "localhost";
        port = 0;
        unixSocket = m_ConnectionInfo.PortOrtSocket.c_str();
    } else {
        port = atoi(m_ConnectionInfo.PortOrtSocket.c_str());
        unixSocket = nullptr;
    }

    m_Mysql = reinterpret_cast<MySQLHandle*>(mysql_real_connect(mysqlInit,
                                m_ConnectionInfo.Host.c_str(),
                                m_ConnectionInfo.User.c_str(),
                                m_ConnectionInfo.Password.c_str(),
                                m_ConnectionInfo.Database.c_str(),
                                port, unixSocket, 0));

    // When we are connected to mysql
    if(m_Mysql) {
        // when we will reconnect to mysql
        if(!m_bReconnecting) {
            printf("MySQL Client Version: %s", mysql_get_client_info());
            printf("MySQL Server Version: %s", mysql_get_server_info(m_Mysql));
        }

        printf("MySQL Connected to Database at %s", m_ConnectionInfo.Database.c_str());
        mysql_autocommit(m_Mysql, 1);
        mysql_set_character_set(m_Mysql, "utf8");
        return 0;
    } else {
        printf("MySQL Could not connect to mysql database at %s: %s", m_ConnectionInfo.Host.c_str(), mysql_error(mysqlInit));
        mysql_close(mysqlInit);
        return mysql_errno(mysqlInit);
    }


}

/**
 * Close the MySQL connection
 *
 * Stops the current worker thread and clears the statement container.
 * Checks whether the MYSQL is still active, ends it and set it to NULL.
 */
void MySQLConnection::Close() {
    // Stop the worker thread before the statements are cleared
    //m_Worker.reset();

    // Clear the statements container...
    m_Statements.clear();

    // Check if MYSQL active and close it
    if(m_Mysql) {
        mysql_close(m_Mysql);
        m_Mysql = nullptr;
    }
}