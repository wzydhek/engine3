/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * DatabaseEntry.cpp
 *
 *  Created on: 14/02/2010
 *      Author: victor
 */

#include "DatabaseEntry.h"

using namespace engine::db::berkeley;

DatabaseEntry::DatabaseEntry() {
	memset(&databaseEntry, 0, sizeof(DBT));

	databaseEntry.flags |= DB_DBT_MALLOC;
}

DatabaseEntry::DatabaseEntry(uint8* data, int size) {
	memset(&databaseEntry, 0, sizeof(DBT));

	databaseEntry.size = size;
	databaseEntry.data = data;

	setUserBuffer(size, true);
}

DatabaseEntry::~DatabaseEntry() {
	//TODO: THIS CRASHES UNDER MSVC link against libdb50dl.lib and set current runtime to multi-thread debug dll
//#ifndef _MSC_VER
	if (!(databaseEntry.flags & DB_DBT_USERMEM) && databaseEntry.data != nullptr)
		free(databaseEntry.data);
//#endif
}

/*DatabaseEntry::DatabaseEntry(byte* data, int offset, int size) {
	memset(&databaseEntry, 0, sizeof(DBT));

	databaseEntry.size = size;
	databaseEntry.data = data + offset;
}*/

DatabaseEntry::DatabaseEntry(Stream* stream) {
	memset(&databaseEntry, 0, sizeof(DBT));

	databaseEntry.size = stream->size();
	databaseEntry.data = stream->getBuffer();

	setUserBuffer(stream->size(), true);
}

void DatabaseEntry::setData(void* addr, int size) {
	databaseEntry.data = addr;
	databaseEntry.size = size;

	setUserBuffer(size, true);
}

void DatabaseEntry::setUserBuffer(int length, bool usermem) {
	databaseEntry.ulen = length;

	if (usermem) {
		databaseEntry.flags |= DB_DBT_USERMEM;
		databaseEntry.flags &= ~DB_DBT_MALLOC;
		databaseEntry.flags &= ~DB_DBT_REALLOC;
	} else {
		databaseEntry.flags &= ~DB_DBT_USERMEM;
		databaseEntry.flags &= ~DB_DBT_REALLOC;
		databaseEntry.flags |= DB_DBT_MALLOC;
	}
}

void DatabaseEntry::setReuseBuffer(bool reuse) {
	if (reuse) {
		databaseEntry.flags &= ~DB_DBT_MALLOC;
		databaseEntry.flags &= ~DB_DBT_USERMEM;
		databaseEntry.flags |= DB_DBT_REALLOC;
	} else {
		databaseEntry.flags &= ~DB_DBT_REALLOC;
		databaseEntry.flags &= ~DB_DBT_USERMEM;
		databaseEntry.flags |= DB_DBT_MALLOC;
	}
}

void* DatabaseEntry::getData() {
	return databaseEntry.data;
}

int DatabaseEntry::getSize() {
	return databaseEntry.size;
}

DBT* DatabaseEntry::getDBT() {
	return &databaseEntry;
}