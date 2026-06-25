/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#include "Packet.h"

Packet::Packet() : Stream(RAW_MAX_SIZE, RAW_MAX_SIZE), ObjectInputStream(), ObjectOutputStream() {
}

Packet::Packet(int size) : Stream(size, RAW_MAX_SIZE), ObjectInputStream(), ObjectOutputStream() {
}

Packet::~Packet() {
}

Packet* Packet::clone(int startoffs) {
	Packet* pack = new Packet();
	copy(pack, startoffs);

	return pack;
}

// inserting methods
void Packet::insertBoolean(bool val) {
	writeBoolean(val);
}

void Packet::insertByte(uint8 val) {
	writeByte(val);
}

void Packet::insertByte(int offs, uint8 val) {
	writeByte(offs, val);
}

void Packet::insertSignedByte(int8 val) {
	writeSignedByte(val);
}

void Packet::insertShort(uint16 val) {
	writeShort(val);
}

void Packet::insertSignedShort(int16 val) {
	writeSignedShort(val);
}

void Packet::insertShort(int offs, uint16 val) {
	writeShort(offs, val);
}

void Packet::insertShortNet(uint16 val) {
	writeShort(htons(val));
}

void Packet::insertInt(uint32 val) {
	writeInt(val);
}

void Packet::insertInt(int offs, uint32 val) {
	writeInt(offs, val);
}

void Packet::insertSignedInt(int32 val) {
	writeSignedInt(val);
}

void Packet::insertIntNet(uint32 val) {
	writeInt(htonl(val));
}

void Packet::insertLong(uint64 val) {
	writeLong(val);
}

void Packet::insertLong(int offs, uint64 val) {
	writeLong(offs, val);
}

void Packet::insertSignedLong(int64 val) {
	writeSignedLong(val);
}

void Packet::insertFloat(float val) {
	writeFloat(val);
}

void Packet::insertDouble(double val) {
	writeDouble(val);
}

void Packet::insertAscii(const char* ascii) {
	int len = strlen(ascii);

	writeShort(len);
	writeStream(ascii, len);
}

void Packet::insertAscii(const char* ascii, int len) {
	writeShort(len);
	writeStream(ascii, len);
}

void Packet::insertAscii(const String& ascii) {
	int len = ascii.length();
	writeShort(len);

	writeStream(ascii.toCharArray(), len);
}

void Packet::insertUnicode(const UnicodeString& str) {
	int len = str.length();
	writeInt(len);

	writeStream((char*)str.toWideCharArray(), len * 2);
}

void Packet::insertStream(const char* buf, int len) {
	writeStream(buf, len);
}

void Packet::insertStream(Stream* stream) {
	writeStream(stream);
}

void Packet::insertStream(Stream* stream, int len) {
	writeStream(stream, len);
}

void Packet::insertCString(const char* buf, bool nullTerminator) {
	char character;

	while ((character = *(buf++))) {
		insertByte(character);
	}

	if (nullTerminator) {
		insertByte(0);
	}
}

// parsing methods
bool Packet::parseBoolean() {
	return readBoolean();
}

uint8 Packet::parseByte() {
	return readByte();
}

uint8 Packet::parseByte(int offs) {
	return readByte(offs);
}

int8 Packet::parseSignedByte() {
	return readSignedByte();
}

int8 Packet::parseSignedByte(int offs) {
	return readSignedByte(offs);
}

uint16 Packet::parseShort() {
	return readShort();
}

int16 Packet::parseSignedShort() {
	return readSignedShort();
}

int16 Packet::parseSignedShort(int offs) {
	return readSignedShort(offs);
}

uint16 Packet::parseShort(int offs) {
	return readShort(offs);
}

uint16 Packet::parseNetShort() {
	return ntohs(readShort());
}

uint16 Packet::parseNetShort(int offs) {
	return ntohs(readShort(offs));
}

uint32 Packet::parseInt() {
	return readInt();
}

uint32 Packet::parseInt(int offs) {
	return readInt(offs);
}

int32 Packet::parseSignedInt() {
	return readSignedInt();
}

int32 Packet::parseSignedInt(int offs) {
	return readSignedInt(offs);
}

uint32 Packet::parseNetInt() {
	return ntohl(readInt());
}

uint32 Packet::parseNetInt(int offs) {
	return ntohl(readInt(offs));
}

uint64 Packet::parseNetLong() {
	uint64 value = readLong();

	return NTOHLL(value);
}

uint64 Packet::parseNetLong(int offs) {
	auto value = readLong(offs);

	return NTOHLL(value);
}

uint64 Packet::parseLong() {
	return readLong();
}

uint64 Packet::parseLong(int offs) {
	return readLong(offs);
}

int64 Packet::parseSignedLong() {
	return readSignedLong();
}

int64 Packet::parseSignedLong(int offs) {
	return readSignedLong(offs);
}

float Packet::parseFloat() {
	return readFloat();
}

double Packet::parseDouble() {
	return readDouble();
}

float Packet::parseFloat(int offs) {
	return readFloat(offs);
}

int Packet::parseAscii(char* ascii) {
	uint16 len = readShort();
	readStream(ascii, (int)len);

	ascii[len] = 0;
	return len;
}

void Packet::parseAscii(String& ascii) {
	uint32 len = readShort();
	shiftOffset(len);

	ascii = String(offset - len, len);
}

String Packet::parseAscii() {
	uint32 len = readShort();
	shiftOffset(len);

	return String(offset - len, len);
}

void Packet::parseAscii(int offs, String& ascii) {
	uint32 len = readShort(offs);

	char* elementOffset = elementData + offs + 2;
	if (elementOffset > end)
		throw StreamIndexOutOfBoundsException(this, offs + 2);

	ascii = String(elementOffset - len, len);
}

void Packet::parseUnicode(UnicodeString& str) {
	uint32 len = readInt();
	uint32 totalLen = len * UnicodeString::UnicodeCharSize::value;

	if (totalLen > MAX_UNICODE_LENGTH) {
		throw StreamIndexOutOfBoundsException(this, MAX_UNICODE_LENGTH);
	}

	shiftOffset(totalLen);

	str.clear();
	str.append(reinterpret_cast<UnicodeString::UnicodeCharType*>((offset - totalLen)), len);
}

UnicodeString Packet::parseUnicode() {
	UnicodeString str;
	parseUnicode(str);

	return str;
}

void Packet::parseUnicode(int offs, UnicodeString& str) {
	uint32 len = readInt(offs);
	uint32 totalLen = len * UnicodeString::UnicodeCharSize::value;

	if (totalLen > MAX_UNICODE_LENGTH) {
		throw StreamIndexOutOfBoundsException(this, MAX_UNICODE_LENGTH);
	}

	char* elementOffset = elementData + offs + 4;

	if (elementOffset > end) {
		throw StreamIndexOutOfBoundsException(this, offs + 4);
	}

	str.clear();
	str.append(reinterpret_cast<UnicodeString::UnicodeCharType*>((elementOffset - totalLen)), len);
}

void Packet::parseStream(char* buf, int len) {
	readStream(buf, len);
}

void Packet::parseStream(Stream* stream, int len) {
	readStream(stream, len);
}