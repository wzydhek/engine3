#include "DisconnectMessage.h"

DisconnectMessage::DisconnectMessage(BaseProtocol* proto) : BasePacket(7) {
	insertShort(0x0500);
	insertInt(proto->getConnectionID());
	insertShort(0x0600);

	setSequencing(false);
}

sys::uint16 DisconnectMessage::parse(Packet* pack) {
	return pack->parseNetShort();
}