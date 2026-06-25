#include "SessionIDRequestMessage.h"

SessionIDRequestMessage::SessionIDRequestMessage() : Packet(10) {
	insertShort(0x0100);
	insertShort(0x00);
	insertShort(0x01);
	insertInt(0x12345678);
}

void SessionIDRequestMessage::parse(Packet* pack, BaseProtocol* prot) {
	sys::uint32 connID = pack->parseInt(6);
	prot->setConnectionID(connID);
}

uint32 SessionIDRequestMessage::parse(Packet* pack) {
	return pack->parseInt(6);
}