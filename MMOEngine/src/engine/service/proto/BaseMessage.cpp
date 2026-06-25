#include "BaseMessage.h"

BaseMessage::BaseMessage() : BasePacket() {
	insertShort(0x0900);
	insertShort(0x0000);
}

BaseMessage::BaseMessage(int size) : BasePacket(size) {
	insertShort(0x0900);
	insertShort(0x0000);
}

BaseMessage::BaseMessage(const Packet* pack, int start) : BasePacket(pack->size() - start) {
	if (start < 0)
		throw PacketIndexOutOfBoundsException(pack, start);

	insertStream(pack->getBuffer() + start, pack->size() - start);

	reset();
}

BaseMessage::BaseMessage(const Packet* pack, int startoffs, int endoffs) : BasePacket(endoffs - startoffs) {
	if (startoffs < 0)
		throw PacketIndexOutOfBoundsException(pack, startoffs);

	if (endoffs > pack->size())
		throw PacketIndexOutOfBoundsException(pack, endoffs);

	insertStream(pack->getBuffer() + startoffs, endoffs - startoffs);

	reset();
}

BaseMessage* BaseMessage::clone(int startoffs) {
	BaseMessage* pack = new BaseMessage();
	copy(pack, startoffs);

	pack->doSeq = doSeq;
	pack->doEncr = doEncr;
	pack->doComp = doComp;
	pack->doCRCTest = doCRCTest;
	return pack;
}