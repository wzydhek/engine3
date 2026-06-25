#include "ObjectOutputStream.h"

ObjectOutputStream::ObjectOutputStream() : Stream() {
}

ObjectOutputStream::ObjectOutputStream(int initsize) : Stream(initsize) {
}

ObjectOutputStream::ObjectOutputStream(int initsize, int capincr) : Stream(initsize, capincr) {
}

ObjectOutputStream::ObjectOutputStream(char *buf, int len) : Stream(buf, len) {
}

		// writing methods
void ObjectOutputStream::writeBoolean(bool val) {
	writePrimitive<uint8>(val);
}

void ObjectOutputStream::writeByte(uint8 val) {
	writePrimitive(val);
}

void ObjectOutputStream::writeByte(int offs, uint8 val) {
	writePrimitiveTo(offs, val);
}

void ObjectOutputStream::writeSignedByte(int8 val) {
	writePrimitive(val);
}

void ObjectOutputStream::writeShort(uint16 val) {
	writePrimitive(val);
}

void ObjectOutputStream::writeSignedShort(int16 val) {
	writePrimitive(val);
}

void ObjectOutputStream::writeShort(int offs, uint16 val) {
	writePrimitiveTo(offs, val);
}

void ObjectOutputStream::writeInt(uint32 val) {
	writePrimitive(val);
}

void ObjectOutputStream::writeInt(int offs, uint32 val) {
	writePrimitiveTo(offs, val);
}

void ObjectOutputStream::writeSignedInt(int32 val) {
	writePrimitive(val);
}

void ObjectOutputStream::writeLong(uint64 val) {
	writePrimitive(val);
}

void ObjectOutputStream::writeLong(int offs, uint64 val) {
	writePrimitiveTo(offs, val);
}

void ObjectOutputStream::writeSignedLong(int64 val) {
	writePrimitive(val);
}

void ObjectOutputStream::writeFloat(float val) {
	writePrimitive(val);
}

void ObjectOutputStream::writeDouble(double val) {
	writePrimitive(val);
}
