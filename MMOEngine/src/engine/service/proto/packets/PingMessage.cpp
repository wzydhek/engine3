#include "PingMessage.h"

PingMessage::PingMessage() : BasePacket(7) {
	insertShort(0x0600);
}

void PingMessage::parse(Packet* pack) {
}