#include "ObjectInputStream.h"

ObjectInputStream::ObjectInputStream() : Stream() {
}

ObjectInputStream::ObjectInputStream(int initsize) : Stream(initsize) {
}

ObjectInputStream::ObjectInputStream(int initsize, int capincr) : Stream(initsize, capincr) {
}

ObjectInputStream::ObjectInputStream(char* buf, int len) : Stream(buf, len) {
}

// reading methods
bool ObjectInputStream::readBoolean() {
	return readPrimitive<uint8>();
}

uint8 ObjectInputStream::readByte() {
	return readPrimitive<uint8>();
}

uint8 ObjectInputStream::readByte(int offs) {
	return readPrimitiveFrom<uint8>(offs);
}

int8 ObjectInputStream::readSignedByte() {
	return readPrimitive<int8>();
}

int8 ObjectInputStream::readSignedByte(int offs) {
	return readPrimitiveFrom<int8>(offs);
}

uint16 ObjectInputStream::readShort() {
	return readPrimitive<uint16>();
}

uint16 ObjectInputStream::readShort(int offs) {
	return readPrimitiveFrom<uint16>(offs);
}

int16 ObjectInputStream::readSignedShort(int offs) {
	return readPrimitiveFrom<int16>(offs);
}

int16 ObjectInputStream::readSignedShort() {
	return readPrimitive<int16>();
}

uint32 ObjectInputStream::readInt() {
	return readPrimitive<uint32>();
}

uint32 ObjectInputStream::readNetInt() {
	return ntohl(readInt());
}

uint32 ObjectInputStream::readInt(int offs) {
	return readPrimitiveFrom<uint32>(offs);
}

int32 ObjectInputStream::readSignedInt() {
	return readPrimitive<int32>();
}

int32 ObjectInputStream::readSignedInt(int offs) {
	return readPrimitiveFrom<int32>(offs);
}

uint64 ObjectInputStream::readLong() {
	return readPrimitive<uint64>();
}

uint64 ObjectInputStream::readLong(int offs) {
	return readPrimitiveFrom<uint64>(offs);
}

int64 ObjectInputStream::readSignedLong() {
	return readPrimitive<int64>();
}

int64 ObjectInputStream::readSignedLong(int offs) {
	return readPrimitiveFrom<int64>(offs);
}

float ObjectInputStream::readFloat() {
	return readPrimitive<float>();
}

float ObjectInputStream::readFloat(int offs) {
	return readPrimitiveFrom<float>(offs);
}

double ObjectInputStream::readDouble() {
	return readPrimitive<double>();
}
