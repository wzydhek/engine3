#include "Message.h"

Message::Message() : Packet() /*, DistributedObject() */ {
	client = nullptr;
	timestampMili = 0;
}

Message::Message(int size) : Packet(size) /*, DistributedObject() */ {
	client = nullptr;
	timestampMili = 0;
}

Message::Message(const Packet* packet, ServiceClient* clt) {
	packet->copy(this, 0);

	client = clt;
	timestampMili = 0;
}

int Message::compareTo(Message* m) {
	uint64 t1 = timestampMili;
	uint64 t2 = m->timestampMili;

	if (t1 < t2)
		return 1;
	else if (t1 > t2)
		return -1;
	else
		return 0;
}

Message* Message::clone(int startoffs) {
	Message* pack = new Message();
	copy(pack, startoffs);

	pack->client = client;

	return pack;
}

bool Message::toBinaryStream(ObjectOutputStream* stream) {
	int size = Packet::size();

	Integer::toBinaryStream(size, stream);

	stream->writeStream(getBuffer(), size);

	return true;
}

bool Message::parseFromBinaryStream(ObjectInputStream* stream) {
	Packet::removeAll();

	int size;

	Integer::parseFromBinaryStream(size, stream);

	writeStream(stream, size);

	return true;
}

// setters and getters
void Message::setClient(ServiceClient* c) {
	client = c;
}

void Message::setTimeStampMili(uint64 ts) {
	timestampMili = ts;
}

uint64 Message::getTimeStampMili() const {
	return timestampMili;
}

ServiceClient* Message::getClient() const {
	return client;
}