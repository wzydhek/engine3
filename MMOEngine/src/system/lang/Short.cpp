#include "Short.h"

Short::Short() : BaseTypeVariable<int16>(0) {
}

Short::Short(int16 val) : BaseTypeVariable<int16>(val) {
}

Short::Short(const Short& val) : BaseTypeVariable<int16>(val) {
}

Short& Short::operator=(const Short& val) {
	if (this == &val) {
		return *this;
	}

	BaseTypeVariable<int16>::operator=(val);

	return *this;
}

bool Short::parseFromString(const String& str, int version) {
	*this = (int16)Integer::valueOf(str);

	return true;
}

bool Short::toString(String& str) const {
	str = String::valueOf((int)*this);

	return true;
}

bool Short::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeSignedShort(get());

	return true;
}

bool Short::parseFromBinaryStream(ObjectInputStream* stream) {
	*this = stream->readSignedShort();

	return true;
}

uint32 Short::hashCode(int16 value) {
	return (uint32)value;
}

UnsignedShort::UnsignedShort() : BaseTypeVariable<uint16>(0) {
}

UnsignedShort::UnsignedShort(uint16 val) : BaseTypeVariable<uint16>(val) {
}

UnsignedShort& UnsignedShort::operator=(const UnsignedShort& val) {
	if (this == &val) {
		return *this;
	}

	BaseTypeVariable<uint16>::operator=(val);

	return *this;
}

bool UnsignedShort::parseFromString(const String& str, int version) {
	*this = (int16)UnsignedInteger::valueOf(str);

	return true;
}

bool UnsignedShort::toString(String& str) const {
	str = String::valueOf((uint32) * this);

	return true;
}

bool UnsignedShort::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeShort(get());

	return true;
}

bool UnsignedShort::parseFromBinaryStream(ObjectInputStream* stream) {
	*this = stream->readShort();

	return true;
}

uint32 UnsignedShort::hashCode(uint16 value) {
	return (uint32)value;
}
