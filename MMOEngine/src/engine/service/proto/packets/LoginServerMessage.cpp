#include "LoginServerMessage.h"

LoginServerMessage::LoginServerMessage() : BasePacket(100) {
	insertShort(0x0900);
	insertShort(0x00);
	insertShort(0x1900);

	insertByte(0x19);
	insertShort(0x02);
	insertInt(0x0E20D7E9);
	insertAscii("LoginServer:29411", 0x11);

	insertByte(0x0A);
	insertShort(0x02);
	insertInt(0x58C07F21);
	insertInt(0x72E3);
}