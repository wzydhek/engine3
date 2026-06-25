#include "SessionIDResponseMessage.h"

SessionIDResponseMessage::SessionIDResponseMessage(BaseProtocol* prot) : Packet(17) {
	insertShort(0x0200);
	insertInt(prot->getConnectionID());
	insertInt(htonl(prot->getSeed()));
	insertByte(0x02);
	insertByte(0x01); // 1
	insertByte(0x04); // 4
	insertByte(0x00);
	insertByte(0x00);
	insertByte(0x01);
	insertByte(0xF0);
}

unsigned int SessionIDResponseMessage::parse(Packet* pack) {
	return ntohl(pack->parseInt(6)); // return recieved crcSeed
}