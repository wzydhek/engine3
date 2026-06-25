/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#include "Integer.h"

#include "system/io/ObjectOutputStream.h"
#include "system/io/ObjectInputStream.h"

#include "NumberFormatException.h"

Integer::Integer() : BaseTypeVariable<int>(0) {
}

Integer::Integer(int val) : BaseTypeVariable<int>(val) {
}

Integer::Integer(const Integer& val) : BaseTypeVariable<int>(val) {
}

Integer& Integer::operator=(const Integer& val) {
	if (this == &val) {
		return *this;
	}

	BaseTypeVariable<int>::operator=(val);

	return *this;
}
int Integer::valueOf(char ch) {
	int digit = ch - '0';
	if (digit < 0 || digit > 9)
		throw NumberFormatException();

	return digit;
}

uint32 Integer::hexvalueOf(const String& str) {
	uint64 val = 0;
	uint64 mul = 1;

	for (int i = str.length() - 1; i >= 0; --i) {
		char c = str.charAt(i);
		int digit;

		if (c >= '0' && c <= '9')
			digit = c - '0';
		else if (c >= 'A' && c <= 'F')
			digit = c - 'A' + 10;
		else if (c >= 'a' && c <= 'f')
			digit = c - 'a' + 10;
		else
			throw NumberFormatException(i);

		val += digit * mul;

		mul *= 16;
	}

	return (uint32) (val);
}

bool Integer::toString(String& str) const {
	str = String::valueOf(*this);

	return true;
}

bool Integer::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeSignedInt(get());

	return true;
}

void Integer::toBinaryStream(int val, ObjectOutputStream* stream) {
	stream->writeSignedInt(val);
}

bool Integer::parseFromString(const String& str, int version) {
	*this = valueOf(str);

	return true;
}

bool Integer::parseFromBinaryStream(ObjectInputStream* stream) {
	*this = stream->readSignedInt();

	return true;
}

void Integer::parseFromBinaryStream(int& val, ObjectInputStream* stream) {
	val = stream->readSignedInt();
}

int Integer::valueOf(const char* str) {
	return atoi(str);
}

int Integer::valueOf(const String& str) {
	return valueOf(str.toCharArray());
}

uint32 Integer::hashCode(int value) {
	uint32 a = value;

	a = (a + 0x7ed55d16) + (a << 12);
	a = (a ^ 0xc761c23c) ^ (a >> 19);
	a = (a + 0x165667b1) + (a << 5);
	a = (a + 0xd3a2646c) ^ (a << 9);
	a = (a + 0xfd7046c5) + (a << 3);
	a = (a ^ 0xb55a4f09) ^ (a >> 16);

	return a;
}

UnsignedInteger::UnsignedInteger() : BaseTypeVariable<uint32>(0) {
}

UnsignedInteger::UnsignedInteger(uint32 val) : BaseTypeVariable<uint32>(val) {
}

UnsignedInteger::UnsignedInteger(const UnsignedInteger& val) : BaseTypeVariable<uint32>(val) {
}

bool UnsignedInteger::toString(String& str) const {
	str = String::valueOf(*this);

	return true;
}

bool UnsignedInteger::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeInt(get());

	return true;
}

bool UnsignedInteger::parseFromString(const String& str, int version) {
	*this = (unsigned int) UnsignedInteger::valueOf(str);

	return true;
}

bool UnsignedInteger::parseFromBinaryStream(ObjectInputStream* stream) {
	*this = stream->readInt();

	return true;
}

unsigned int UnsignedInteger::valueOf(const String& str) {
	unsigned int val = 0;
	unsigned int mul = 1;

	for (int i = str.length() - 1; i >= 0; --i) {
		int digit = Integer::valueOf(str.charAt(i));

		val += digit * mul;

		mul *= 10;
	}

	return val;
}

uint32 UnsignedInteger::hashCode(uint32 value) {
	uint32 a = value;

	a = (a + 0x7ed55d16) + (a << 12);
	a = (a ^ 0xc761c23c) ^ (a >> 19);
	a = (a + 0x165667b1) + (a << 5);
	a = (a + 0xd3a2646c) ^ (a << 9);
	a = (a + 0xfd7046c5) + (a << 3);
	a = (a ^ 0xb55a4f09) ^ (a >> 16);

	return a;
}
