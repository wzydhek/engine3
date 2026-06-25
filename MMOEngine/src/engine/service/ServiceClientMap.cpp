#include "ServiceClientMap.h"

ServiceClientMap::ServiceClientMap(int maxconn) : HashTable<uint64, ServiceClient*>((int)(maxconn * 1.25f)), HashTableIterator<uint64, ServiceClient*>(this) {
	maxConnections = maxconn;

	setNullValue(nullptr);
}

bool ServiceClientMap::add(ServiceClient* client) {
	if (HashTable<uint64, ServiceClient*>::put(client->getNetworkID(), client) == nullptr) {
		client->acquire();

		return true;
	} else
		return false;
}

bool ServiceClientMap::remove(ServiceClient* client) {
	if (HashTable<uint64, ServiceClient*>::remove(client->getNetworkID()) != nullptr) {
		client->release();

		return true;
	} else
		return false;
}