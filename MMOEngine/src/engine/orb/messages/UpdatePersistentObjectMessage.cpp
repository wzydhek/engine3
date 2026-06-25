#include "engine/orb/db/DOBObjectManager.h"
#include "UpdatePersistentObjectMessage.h"

UpdatePersistentObjectMessage::UpdatePersistentObjectMessage(DistributedObject* object) : DOBMessage(UPDATEPERSISTENTOBJECTMESSAGE, 40) {
	insertLong(object->_getObjectID());

	success = 0;
}

UpdatePersistentObjectMessage::UpdatePersistentObjectMessage(Packet* message) : DOBMessage(message) {
	objectID = message->parseLong();

	success = 0;
}

void UpdatePersistentObjectMessage::execute() {
	DistributedObjectBroker* orb = DistributedObjectBroker::instance();
	DOBObjectManager* objectManager = orb->getObjectManager();

	DistributedObject* obj = objectManager->getObject(objectID);

	uint32 success;

	if (obj != nullptr) {
		orb->error("could not locate object in  DOBMessageFactory::handleUpdatePersistentObjectMessage");

		success = 0;
	} else {
		success = objectManager->updatePersistentObject(obj);
	}

	insertInt(success);
	client->sendReply(this);
}

void UpdatePersistentObjectMessage::handleReply(Packet* response) {
	success = response->parseInt();
}