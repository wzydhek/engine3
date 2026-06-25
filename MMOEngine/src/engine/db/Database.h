/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "DatabaseException.h"
#include "ResultSet.h"

namespace engine {
namespace db {

class Database {
public:
	Database() {
	}

	virtual ~Database() {
	}

	virtual void connect(const String& dbname, const String& user,
			const String& passw, int port) {

	}

	virtual void close() {

	}

	virtual void executeStatement(const char* statement) {

	}

	virtual void executeStatement(const String& statement) {

	}

	virtual void executeStatement(const StringBuffer& statement) {

	}

	virtual ResultSet* executeQuery(const char* statement) {
		return nullptr;
	}

	virtual ResultSet* executeQuery(const String& statement) {
		return nullptr;
	}

	virtual ResultSet* executeQuery(const StringBuffer& statement) {
		return nullptr;
	}

	virtual void commit() {

	}

	virtual void rollback() {

	}

	virtual void autocommit(bool doCommit) {

	}

	virtual int compareTo(const Database* database) const {
		return 0;
	}

	static void escapeString(String& s);
};

} // namespace db
} // namespace engine

using namespace engine::db;
