#include "NetStatusResponseMessage.h"

NetStatusResponseMessage::NetStatusResponseMessage(sys::uint16 tick) : BasePacket(40) {
	insertShort(0x0800);
	insertShortNet(tick);

	insertInt(0x00000000);
	insertInt(0x00000000);
	insertInt(0x00000000);
	insertInt(0x00000000);
	insertInt(0x00000000);
	insertInt(0x00000000);
	insertInt(0x00000000);
	insertInt(0x00000000);
	insertInt(0x00000000);

	setSequencing(false);
	setCompression(true);
	setCRCChecking(false);
}

sys::uint16 NetStatusResponseMessage::parseTick(Packet* pack) {
	return pack->parseNetShort(2);
}