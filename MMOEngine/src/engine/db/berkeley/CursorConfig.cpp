#include "CursorConfig.h"

CursorConfig::CursorConfig() {
	flags = 0;
}

CursorConfig::CursorConfig(uint32 flag) {
	flags = flag;
}

void CursorConfig::setReadCommitted(bool readCommitted) {
	if (readCommitted)
		flags |= DB_READ_COMMITTED;
	else
		flags &= ~DB_READ_COMMITTED;
}

void CursorConfig::setReadUncommitted(bool readUncommitted) {
	if (readUncommitted)
		flags |= DB_READ_UNCOMMITTED;
	else
		flags &= ~DB_READ_UNCOMMITTED;
}

void CursorConfig::setSnapshot(bool snapshot) {
	if (snapshot)
		flags |= DB_TXN_SNAPSHOT;
	else
		flags &= ~DB_TXN_SNAPSHOT;
}

void CursorConfig::setWriteCursor(bool writeCursor) {
	if (writeCursor)
		flags |= DB_WRITECURSOR;
	else
		flags &= ~DB_WRITECURSOR;
}

uint32 CursorConfig::getFlags() const {
	return flags;
}