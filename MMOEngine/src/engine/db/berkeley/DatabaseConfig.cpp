#include "DatabaseConfig.h"

DatabaseConfig::DatabaseConfig() {
	databaseFlags = 0;
	databaseType = DatabaseType::UNKNOWN;
	duplicates = false;
}

void DatabaseConfig::setAllowCreate(bool allowCreate) {
	if (!allowCreate)
		databaseFlags &= ~DB_CREATE;
	else
		databaseFlags |= DB_CREATE;
}

void DatabaseConfig::setReadOnly(bool val) {
	if (!val)
		databaseFlags &= ~DB_RDONLY;
	else
		databaseFlags |= DB_RDONLY;
}

void DatabaseConfig::setDuplicates(bool val) {
	duplicates = val;
}

void DatabaseConfig::setAutoCommit(bool transactional) {
	if (transactional)
		databaseFlags |= DB_AUTO_COMMIT;
	else
		databaseFlags &= ~DB_AUTO_COMMIT;
}

void DatabaseConfig::setThreaded(bool threaded) {
	if (threaded)
		databaseFlags |= DB_THREAD;
	else
		databaseFlags &= ~DB_THREAD;
}

void DatabaseConfig::setReadUncommited(bool value) {
	if (value)
		databaseFlags |= DB_READ_UNCOMMITTED;
	else
		databaseFlags &= ~DB_READ_UNCOMMITTED;
}

void DatabaseConfig::setMultiVersionConcurrencyControl(bool value) {
	if (value)
		databaseFlags |= DB_MULTIVERSION;
	else
		databaseFlags &= ~DB_MULTIVERSION;
}

void DatabaseConfig::setType(DBTYPE type) {
	databaseType = type;
}

uint32 DatabaseConfig::getDatabaseFlags() const {
	return databaseFlags;
}

DBTYPE DatabaseConfig::getDatabaseType() const {
	return databaseType;
}

bool DatabaseConfig::hasDuplicates() const {
	return duplicates;
}