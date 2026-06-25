/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * Cursor.cpp
 *
 *  Created on: 15/02/2010
 *      Author: victor
 */

#include "engine/db/DatabaseException.h"

#include "Cursor.h"
#include "DatabaseEntry.h"
#include "engine/db/berkeley/Environment.h"

using namespace engine::db::berkeley;

CursorConfig CursorConfig::DEFAULT;

Cursor::Cursor(BerkeleyDatabase* database, DBC* dbcursor, const CursorConfig& config) {
	Cursor::database = database;
	Cursor::config = config;

	dbc = dbcursor;
}

Cursor::~Cursor() {
	if (dbc != nullptr) {
		close();
	}
}

int Cursor::close() {
	Locker locker(&Environment::guard);

	int ret = dbc->close(dbc);

	dbc = nullptr;

	return ret;
}

int Cursor::del(uint32 flags) {
	return dbc->del(dbc, flags);
}

Cursor* Cursor::dup(bool samePosition) {
	uint32 flags = 0;

	if (samePosition)
		flags = DB_POSITION;

	DBC* dbdup = nullptr;

	int res = dbc->dup(dbc, &dbdup, flags);

	if (res != 0) {
		throw DatabaseException("error duplicating cursor with ret " + String::valueOf(res));
	}

	Cursor* cursor = new Cursor(database, dbdup, config);
	return cursor;
}

int Cursor::get(DatabaseEntry* key, DatabaseEntry* data, uint32 flags) {
	return dbc->get(dbc, key->getDBT(), data->getDBT(), flags);
}

int Cursor::getRecordNumber(DatabaseEntry* data, uint32 lockMode) {
	return dbc->get(dbc, nullptr, data->getDBT(), DB_GET_RECNO | lockMode);
}

int Cursor::pget(DatabaseEntry* key, DatabaseEntry* primaryKey, DatabaseEntry* data, uint32 flags) {
	return dbc->pget(dbc, key->getDBT(), primaryKey->getDBT(), data->getDBT(), flags);
}

int Cursor::put(DatabaseEntry* key, DatabaseEntry* data, uint32 flags) {
	return dbc->put(dbc, key->getDBT(), data->getDBT(), flags);
}

int Cursor::putCurrent(DatabaseEntry* data) {
	return dbc->put(dbc, nullptr, data->getDBT(), DB_CURRENT);
}

int Cursor::getCurrent(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_CURRENT | lockMode);
}

int Cursor::getFirst(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_FIRST | lockMode);
}

int Cursor::getLast(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_LAST | lockMode);
}

int Cursor::getNext(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_NEXT | lockMode);
}

int Cursor::pGetSet(DatabaseEntry* key, DatabaseEntry* primaryKey, DatabaseEntry* data, uint32 lockMode) {
	return pget(key, primaryKey, data, DB_SET | lockMode);
}

int Cursor::pGetNext(DatabaseEntry* key, DatabaseEntry* primaryKey, DatabaseEntry* data, uint32 lockMode) {
	return pget(key, primaryKey, data, DB_NEXT | lockMode);
}

int Cursor::getNextMultiple(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_MULTIPLE_KEY | DB_NEXT | lockMode);
}

int Cursor::getNextDup(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_NEXT_DUP | lockMode);
}

int Cursor::pGetNextDup(DatabaseEntry* key, DatabaseEntry* primaryKey, DatabaseEntry* data, uint32 lockMode) {
	return pget(key, primaryKey, data, DB_NEXT_DUP | lockMode);
}

int Cursor::getNextNoDup(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_NEXT_NODUP | lockMode);
}

int Cursor::getPrev(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_PREV | lockMode);
}

int Cursor::getPrevDup(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_PREV_DUP | lockMode);
}

int Cursor::getPrevNoDup(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_PREV_NODUP | lockMode);
}

int Cursor::getSearchBoth(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_GET_BOTH | lockMode);
}

int Cursor::getSearchBothRange(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_GET_BOTH_RANGE | lockMode);
}

int Cursor::getSearchKey(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_SET | lockMode);
}

int Cursor::getSearchKeyRange(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_SET_RANGE | lockMode);
}

int Cursor::getSearchRecordNumber(DatabaseEntry* key, DatabaseEntry* data, uint32 lockMode) {
	return get(key, data, DB_SET_RECNO | lockMode);
}

int Cursor::putAfter(DatabaseEntry* key, DatabaseEntry* data) {
	return put(key, data, DB_AFTER);
}

int Cursor::putBefore(DatabaseEntry* key, DatabaseEntry* data) {
	return put(key, data, DB_BEFORE);
}

int Cursor::putKeyFirst(DatabaseEntry* key, DatabaseEntry* data) {
	return put(key, data, DB_KEYFIRST);
}

int Cursor::putKeyLast(DatabaseEntry* key, DatabaseEntry* data) {
	return put(key, data, DB_KEYLAST);
}

int Cursor::putNoDupData(DatabaseEntry* key, DatabaseEntry* data) {
	return put(key, data, DB_NODUPDATA);
}

CursorConfig Cursor::getConfig() {
	return config;
}

BerkeleyDatabase* Cursor::getDatabase() {
	return database;
}