#include "AcknowledgeOkMessage.h"

AcknowledgeOkMessage::AcknowledgeOkMessage(sys::uint16 seq) : BasePacket(17) {
	insertShort(0x0300);
	insertByte(0x04);
	insertShort(0x1500);
	insertShortNet(seq);
	insertByte(0x06);
	insertShort(0x0001);
	insertInt(0xA16CF9AF);

	setSequencing(false);
}

void AcknowledgeOkMessage::parseOk(Packet* pack) {
	pack->parseInt();
}