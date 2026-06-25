/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
//
// Created by Victor Popovici on 14/10/16.
//

#include "InvokeMethodMessage.h"

#include "engine/orb/DistributedObjectBroker.h"


InvokeMethodMessage::InvokeMethodMessage(uint64 objectid, sys::uint32 methid, sys::uint32 invid, bool async) : DOBMessage(INVOKEMETHODMESSAGE, 40) {
	insertLong(objectid);

	insertInt(methid);
	insertInt(invid);

	insertBoolean(async);

	packet = nullptr;
	objectID = 0;
	methodID = 0;
	invocationID = 0;

	this->async = async;
}

InvokeMethodMessage::InvokeMethodMessage(Packet* message) : DOBMessage(message) {
	objectID = message->parseLong();

	methodID = message->parseInt();
	invocationID = message->parseInt();

	async = message->parseBoolean();

	packet = message->clone();
}

InvokeMethodMessage::~InvokeMethodMessage() {
	if (packet != nullptr)
		delete packet;
}

void InvokeMethodMessage::runMethod() {
	DistributedObjectBroker* orb = DistributedObjectBroker::instance();

	//printf("trying to get adapter in invoke method fod oid:%d", (int) objectID);

	DistributedObjectAdapter* adapter = orb->getObjectAdapter(objectID);
	if (adapter == nullptr) {
		orb->error("object not found for method invocation for oid: " + String::valueOf(objectID));
		return;
	}

	DistributedMethod invocation(orb, this);
	adapter->invokeMethod(methodID, &invocation);

	if (!async) {
		DOBMessage* response = (DOBMessage*) invocation.getResponseMessage();
		client->sendReply(response);
	}
}

void InvokeMethodMessage::execute() {
	if (async) {
		class RunTask : public Task {
		protected:
			InvokeMethodMessage* method;

		public:
			RunTask(InvokeMethodMessage* method) : method(method) {

			}

			void run() {
				method->runMethod();
			}
		};

		RunTask* task = new RunTask(this);
		task->execute();
	} else {
		runMethod();
	}

}

void InvokeMethodMessage::handleReply(Packet* resp) {
	packet = resp->clone();
}

Packet* InvokeMethodMessage::getResponseMessage() {
	return packet;
}

bool InvokeMethodMessage::getBooleanParameter() {
	return packet->parseBoolean();
}

byte InvokeMethodMessage::getByteParameter() {
	return packet->parseByte();
}

char InvokeMethodMessage::getSignedCharParameter() {
	return packet->parseSignedByte();
}

unsigned char InvokeMethodMessage::getUnsignedCharParameter() {
	return packet->parseByte();
}

int InvokeMethodMessage::getSignedIntParameter() {
	return packet->parseSignedInt();
}

unsigned int InvokeMethodMessage::getUnsignedIntParameter() {
	return packet->parseInt();
}

long long InvokeMethodMessage::getSignedLongParameter() {
	return packet->parseSignedLong();
}

unsigned long long InvokeMethodMessage::getUnsignedLongParameter() {
	return packet->parseLong();
}

short InvokeMethodMessage::getSignedShortParameter() {
	return packet->parseSignedShort();
}

unsigned short InvokeMethodMessage::getUnsignedShortParameter() {
	return packet->parseShort();
}

float InvokeMethodMessage::getFloatParameter() {
	return packet->parseFloat();
}

double InvokeMethodMessage::getDoubleParameter() {
	return packet->parseDouble();
}

String& InvokeMethodMessage::getAsciiParameter(String& ascii) {
	packet->parseAscii(ascii);

	return ascii;
}

UnicodeString& InvokeMethodMessage::getUnicodeParameter(UnicodeString& str) {
	packet->parseUnicode(str);

	return str;
}

Packet* InvokeMethodMessage::getIncomingPacket() {
	return packet;
}