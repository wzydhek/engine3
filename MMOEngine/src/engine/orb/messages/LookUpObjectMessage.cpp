#include "LookUpObjectMessage.h"

LookUpObjectMessage::LookUpObjectMessage(const String& name) : DOBMessage(LOOKUPOBJECTMESSAGE, 40) {
	insertAscii(name);

	found = false;
	objectID = 0;
}

LookUpObjectMessage::LookUpObjectMessage(Packet* message) : DOBMessage(message) {
	message->parseAscii(name);

	found = false;
	objectID = 0;
}

void LookUpObjectMessage::execute() {
	DistributedObject* obj = DistributedObjectBroker::instance()->lookUp(name);

	if (obj != nullptr) {
		insertBoolean(true);
		insertAscii(obj->_getClassName());
		insertLong(obj->_getObjectID());
	} else {
		insertBoolean(false);
	}

	client->sendReply(this);
}

void LookUpObjectMessage::handleReply(Packet* message) {
	found = message->parseBoolean();

	if (found) {
		message->parseAscii(className);

		objectID = message->parseLong();
	}
}

bool LookUpObjectMessage::isFound() {
	return found;
}

const String& LookUpObjectMessage::getClassName() {
	return className;
}

uint64 LookUpObjectMessage::getObjectID() {
	return objectID;
}