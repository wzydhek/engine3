#include "Byte.h"

Byte::Byte() : UnsignedCharacter(0) {
}

Byte::Byte(unsigned char val) : UnsignedCharacter(val) {
}

Byte::Byte(const Byte& val) : UnsignedCharacter(val) {
}

Byte& Byte::operator=(const Byte& b) {
	if (this == &b) {
		return *this;
	}

	UnsignedCharacter::operator=(b);

	return *this;
}

bool Byte::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeByte(get());

	return true;
}

bool Byte::parseFromBinaryStream(ObjectInputStream* stream) {
	*this = stream->readByte();

	return true;
}

bool Byte::toString(String& str) const {
	str = String::valueOf((unsigned int)get());

	return true;
}

bool Byte::parseFromString(const String& str, int version0) {
	*this = (unsigned char)UnsignedInteger::valueOf(str);

	return true;
}