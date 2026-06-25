#include "LookUpObjectByIDMessage.h"

LookUpObjectByIDMessage::LookUpObjectByIDMessage(uint64 objectid) : DOBMessage(LOOKUPOBJECTBYIDMESSAGE, 20), objectid(objectid) {
	insertLong(objectid);

	found = false;
}

LookUpObjectByIDMessage::LookUpObjectByIDMessage(Packet* message) : DOBMessage(message) {
	objectid = message->parseLong();

	found = false;
}

void LookUpObjectByIDMessage::execute() {
	DistributedObjectBroker* broker = DistributedObjectBroker::instance();
	DOBObjectManager* objectManager = broker->getObjectManager();

	DistributedObject* obj = objectManager->getObject(objectid);

	if (obj != nullptr) {
		insertBoolean(true);
		insertAscii(obj->_getClassName());
		insertAscii(obj->_getName());

		broker->debug() << "looked up 0x" << objectid << " with name \'" << obj->_getName() << "\' (" << obj->_getClassName() << ")";
	} else
		insertBoolean(false);

	client->sendReply(this);
}

void LookUpObjectByIDMessage::handleReply(Packet* message) {
	found = message->parseBoolean();

	if (found) {
		message->parseAscii(className);
		message->parseAscii(name);
	}
}

const String& LookUpObjectByIDMessage::getClassName() const {
	return className;
}

const String& LookUpObjectByIDMessage::getName() const {
	return name;
}

bool LookUpObjectByIDMessage::isFound() const {
	return found;
}