/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * Transaction.cpp
 *
 *  Created on: 14/02/2010
 *      Author: victor
 */

#include "BTransaction.h"

using namespace engine::db::berkeley;

TransactionConfig TransactionConfig::DEFAULT;

int Transaction::abort() NO_THREAD_SAFETY_ANALYSIS {
	Locker guard(&Environment::guard);

	int ret = transaction->abort(transaction);

	//transaction = nullptr;

	delete this;

	return ret;
}

/**
 * End the transaction.
 */

int Transaction::commit(uint32 flags) NO_THREAD_SAFETY_ANALYSIS {
	Locker guard(&Environment::guard);

	int ret = transaction->commit(transaction, flags);

	//transaction = nullptr;

	delete this;

	return ret;
}

int Transaction::commitNoSync() NO_THREAD_SAFETY_ANALYSIS {
	return commit(DB_TXN_NOSYNC);
}

int Transaction::commitSync() NO_THREAD_SAFETY_ANALYSIS {
	return commit(DB_TXN_SYNC);
}

DB_TXN* Transaction::getDBTXN() const {
	return transaction;
}

DB_TXN** Transaction::getDBTXNPTR() {
	return &transaction;
}