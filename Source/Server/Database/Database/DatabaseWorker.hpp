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

#ifndef SERENITY_DATABASEWORKER_HPP
#define SERENITY_DATABASEWORKER_HPP

#include "Defines.hpp"

#include <atomic>
#include <thread>

template<typename T>
class ProducerConsumerQueue;

class MySQLConnection;
class SQLOperation;

class SC_DATABASE_API DatabaseWorker {
public:
    DatabaseWorker(ProducerConsumerQueue<SQLOperation*>* newQueue, MySQLConnection* connection);
    ~DatabaseWorker();

private:
    ProducerConsumerQueue<SQLOperation*>* m_Queue;
    MySQLConnection* m_Connection;

    void WorkerThread();
    std::thread m_WorkerThread;

    std::atomic<bool> m_CancelationToken;

    DatabaseWorker(DatabaseWorker const& right) = delete;
    DatabaseWorker& operator = (DatabaseWorker const& right) = delete;
};


#endif //SERENITY_DATABASEWORKER_HPP
