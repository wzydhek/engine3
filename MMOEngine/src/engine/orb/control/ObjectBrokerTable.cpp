#include "ObjectBrokerTable.h"

void ObjectBrokerTable::add(ObjectBroker* broker) {
	objectBrokers.add(broker);
}

void ObjectBrokerTable::remove(ObjectBroker* broker) {
	objectBrokers.remove(broker);
}

HashSetIterator<ObjectBroker*> ObjectBrokerTable::iterator() {
	return objectBrokers.iterator();
}

int ObjectBrokerTable::getBrokerCount() {
	return objectBrokers.size();
}