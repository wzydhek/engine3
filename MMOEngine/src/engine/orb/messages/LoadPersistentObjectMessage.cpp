#include "engine/orb/db/DOBObjectManager.h"
#include "LoadPersistentObjectMessage.h"

LoadPersistentObjectMessage::LoadPersistentObjectMessage(uint64 objectid) : DOBMessage(LOADPERSISTENTOBJECTMESSAGE, 40), objectID(objectid) {
	insertLong(objectid);

	found = false;
}

LoadPersistentObjectMessage::LoadPersistentObjectMessage(Packet* message) : DOBMessage(message) {
	objectID = message->parseLong();

	found = false;
}

void LoadPersistentObjectMessage::execute() {
	DistributedObjectBroker* orb = DistributedObjectBroker::instance();
	DOBObjectManager* objectManager = orb->getObjectManager();

	DistributedObject* obj = objectManager->loadPersistentObject(objectID);

	if (obj != nullptr) {
		insertBoolean(true);
		insertAscii(obj->_getClassName());
		insertLong(obj->_getObjectID());
	} else
		insertByte(0);

	client->sendReply(this);
}

void LoadPersistentObjectMessage::handleReply(Packet* response) {
	found = response->parseBoolean();
}

bool LoadPersistentObjectMessage::isFound() {
	return found;
}