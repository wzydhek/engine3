#include "TransactionAbortedException.h"
#include "TransactionalObjectHeader.h"

TransactionAbortedException::TransactionAbortedException() {
	Transaction* currentTransaction = Transaction::currentTransaction();

	currentTransaction->setState(Transaction::ABORTED);
}