/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "engine/util/Singleton.h"
#include "engine/db/Database.h"

namespace engine {
  namespace db {
    namespace mysql {

    class MysqlDatabaseManager : public Singleton<MysqlDatabaseManager>, public Object {
    	ThreadLocal<VectorSet<Database*>* > modifiedDatabases;

    public:
    	void commitModifiedDatabases();
    	void rollbackModifiedDatabases();

    	void addModifiedDatabase(Database* database);

    protected:
    	VectorSet<Database*>* getLocalModifiedDatabases();

    };

    } // namespace mysql
  } // namespace db
} // namespace engine

using namespace engine::db::mysql;
