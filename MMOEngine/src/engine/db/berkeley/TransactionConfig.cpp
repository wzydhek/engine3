#include "TransactionConfig.h"

TransactionConfig::TransactionConfig() {
	transactionFlags = 0;
}

void TransactionConfig::setNoSync(bool noSync) {
	if (noSync)
		transactionFlags |= DB_TXN_NOSYNC;
	else
		transactionFlags &= ~DB_TXN_NOSYNC;
}

void TransactionConfig::setNoWait(bool noWait) {
	if (noWait)
		transactionFlags |= DB_TXN_NOWAIT;
	else
		transactionFlags &= ~DB_TXN_NOWAIT;
}

void TransactionConfig::setReadCommitted(bool readCommitted) {
	if (readCommitted)
		transactionFlags |= DB_READ_COMMITTED;
	else
		transactionFlags &= ~DB_READ_COMMITTED;
}

void TransactionConfig::setReadUncommitted(bool readUncommitted) {
	if (readUncommitted)
		transactionFlags |= DB_READ_UNCOMMITTED;
	else
		transactionFlags &= ~DB_READ_UNCOMMITTED;
}

void TransactionConfig::setSnapshot(bool snapshot) {
	if (snapshot)
		transactionFlags |= DB_TXN_SNAPSHOT;
	else
		transactionFlags &= ~DB_TXN_SNAPSHOT;
}

void TransactionConfig::setSync(bool sync) {
	if (sync)
		transactionFlags |= DB_TXN_SYNC;
	else
		transactionFlags &= ~DB_TXN_SYNC;
}

void TransactionConfig::setWait(bool wait) {
	if (wait)
		transactionFlags |= DB_TXN_WAIT;
	else
		transactionFlags &= ~DB_TXN_WAIT;
}

void TransactionConfig::setWriteNoSync(bool writeNoSync) {
	if (writeNoSync)
		transactionFlags |= DB_TXN_WRITE_NOSYNC;
	else
		transactionFlags &= ~DB_TXN_WRITE_NOSYNC;
}

 uint32 TransactionConfig::getFlags() const {
	return transactionFlags;
}