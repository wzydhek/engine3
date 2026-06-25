#include "OutOfOrderMessage.h"

OutOfOrderMessage::OutOfOrderMessage(sys::uint16 seq) : BasePacket(7) {
	insertShort(0x1100);
	insertShortNet(seq);

	setSequencing(false);
}

sys::uint16 OutOfOrderMessage::parse(Packet* pack) {
	return pack->parseNetShort();
}