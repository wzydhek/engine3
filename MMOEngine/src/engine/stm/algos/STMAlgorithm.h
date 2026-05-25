/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * STMCommitStrategy.h
 *
 *  Created on: 11/11/2011
 *      Author: victor
 */

#pragma once

namespace engine {
 namespace stm {

 	 class Transaction;

 	 //template<class O> class TransactionalObjectHeader;

 	 class STMAlgorithm {
 	 public:
 		STMAlgorithm() {

 		}

 		virtual ~STMAlgorithm() {

 		}

 		virtual bool doCommit(Transaction* transaction) = 0;

 	 };
 }
}
