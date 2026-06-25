/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * Transaction.h
 *
 *  Created on: 14/02/2010
 *      Author: victor
 */

#pragma once

#include <db.h>
#include "system/platform.h"
#include "system/thread/atomic/AtomicReference.h"
#include "Environment.h"

namespace engine {
  namespace db {
    namespace berkeley {

	class Transaction {
	protected:
		DB_TXN* transaction{nullptr};

		Transaction() {
		}

	public:
		/**
		 * Cause an abnormal termination of the transaction, deletes this from memory
		 *
		 */
		int abort() NO_THREAD_SAFETY_ANALYSIS;

		/**
		 * End the transaction, deletes this from memory regarding result
		 */
		int commit(uint32 flags = 0) NO_THREAD_SAFETY_ANALYSIS;

		/**
		 * End the transaction, not committing synchronously, deletes this from memory regarding result
		 */
		int commitNoSync() NO_THREAD_SAFETY_ANALYSIS;

		/**
		 * End the transaction, committing synchronously, deletes this from memory regarding result
		 */
		int commitSync() NO_THREAD_SAFETY_ANALYSIS;

		DB_TXN* getDBTXN() const;

		DB_TXN** getDBTXNPTR();

		friend class Environment;

	};

    } // namespace berkeley
  } // namespace db
} // namespace engine

using namespace engine::db::berkeley;
