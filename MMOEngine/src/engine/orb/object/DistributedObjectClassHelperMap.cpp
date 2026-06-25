#include "DistributedObjectClassHelperMap.h"

DistributedObjectClassHelperMap::DistributedObjectClassHelperMap() : HashTable<String, DistributedObjectClassHelper*>(1000) {
}

DistributedObjectClassHelperMap::~DistributedObjectClassHelperMap() {
	HashTableIterator<String, DistributedObjectClassHelper*> iter(this);

	while (iter.hasNext()) {
		String& helpername = iter.getNextKey();
		DistributedObjectClassHelper* helper = remove(helpername);

		// TODO: fix crash
		// helper->finalizeHelper();
	}
}