#include "ErrorMessage.h"

ErrorMessage::ErrorMessage(const String& ErrorType, const String& ErrorMsg, bool Fatal) : BasePacket(50) {
	insertShort(0x03);
	insertAscii(ErrorType);
	insertAscii(ErrorMsg);
	insertByte(Fatal);
}