#include "UndeployObjectMessage.h"

UndeployObjectMessage::UndeployObjectMessage(const String& name) : DOBMessage(UNDEPLOYOBJECTMESSAGE, 40) {
	insertAscii(name);

	objectID = 0;
}

UndeployObjectMessage::UndeployObjectMessage(Packet* message) : DOBMessage(message) {
	message->parseAscii(name);

	objectID = 0;
}

void UndeployObjectMessage::execute() {
	DistributedObjectBroker* broker = DistributedObjectBroker::instance();

	DistributedObjectStub* obj = nullptr;
	try {
		obj = broker->undeployRemote(name);
	} catch (const Exception& e) {
		e.printStackTrace();
	}

	uint64 objectID = 0;
	if (obj != nullptr)
		objectID = obj->_getObjectID();

	insertLong(objectID);

	client->sendReply(this);
}

void UndeployObjectMessage::handleReply(Packet* message) {
	objectID = message->parseLong();
}

uint64 UndeployObjectMessage::getObjectID() {
	return objectID;
}