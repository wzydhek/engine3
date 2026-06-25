#include "StandaloneBaseMessage.h"

StandaloneBaseMessage::StandaloneBaseMessage() : BasePacket() {
	setSequencing(false);
}

StandaloneBaseMessage::StandaloneBaseMessage(int size) : BasePacket(size) {
	setSequencing(false);
}