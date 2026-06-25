#include "PacketIndexOutOfBoundsException.h"

PacketIndexOutOfBoundsException::PacketIndexOutOfBoundsException(const Packet* pack, int index) : Exception() {
	packet = pack;

	StringBuffer str;
	str << "PacketIndexOutOfBoundsException at " << index << "\n";
	message = str.toString();
}

const Packet* PacketIndexOutOfBoundsException::getPacket() const {
	return packet;
}