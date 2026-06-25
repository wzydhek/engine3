#include "NetStatusRequestMessage.h"

NetStatusRequestMessage::NetStatusRequestMessage(sys::uint16 tick) : BasePacket(7) {
	insertShort(0x0700);
	insertShortNet(tick);

	setSequencing(false);
	setCompression(true);
}

sys::uint16 NetStatusRequestMessage::parseTick(Packet* pack) {
	return pack->parseNetShort(2);
}