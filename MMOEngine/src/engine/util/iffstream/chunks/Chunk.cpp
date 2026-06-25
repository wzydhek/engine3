/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#include "Chunk.h"

Chunk::Chunk(Chunk* par, uint32 id, uint32 size, char* data) {
	writeStream(data, size);
	reset();

	parent = par;

	chunkID = id;
	chunkSize = size;

	lastOpenedSubChunk = -1;

	iffStream = nullptr;
}

Chunk::~Chunk() {
	subChunks.forEach([](auto chunk) {
		delete chunk;
	});
}

void Chunk::parseData() {
}

void Chunk::setIffStream(IffStream* iff) {
	iffStream = iff;
}

IffStream* Chunk::getIffStream() {
	return iffStream;
}

void Chunk::setLastOpenedSubChunk(int value) {
	lastOpenedSubChunk = value;
}

void Chunk::getChildren(Vector<Chunk*>& child) {
	child = subChunks;
}

bool Chunk::isFORM() {
	return chunkID == FORM;
}

bool Chunk::isDATA() {
	return chunkID == DATA;
}

Chunk* Chunk::getParent() {
	return parent;
}

void Chunk::addChunk(Chunk* chunk) {
	subChunks.add(chunk);
}

Chunk* Chunk::getChunk(int idx) {
	return subChunks.get(idx);
}

Chunk* Chunk::getNextChunk() {
	return subChunks.get(++lastOpenedSubChunk);
}

uint32 Chunk::getChunksSize() {
	return subChunks.size();
}

int Chunk::getLastOpenedChunkIdx() {
	return lastOpenedSubChunk;
}

uint32 Chunk::getChunkID() {
	return chunkID;
}

int Chunk::getChunkSize() {
	return chunkSize;
}

void Chunk::readString(String& str) {
	StringBuffer stream;
	char byte;

	while ((byte = readSignedByte()) != 0)
		stream << byte;

	str = stream.toString();
}

String Chunk::readString() {
	String val;
	readString(val);

	return val;
}

Matrix4 Chunk::readMatrix3x4Transform() {
	Matrix4 mat;

	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 4; ++y) {
			mat[x][y] = readFloat();
		}
	}

	return mat;
}

Vector3 Chunk::readVector3() {
	Vector3 vec;

	for (int i = 0; i < 3; ++i) {
		vec[i] = readFloat();
	}

	return vec;
}

Vector4 Chunk::readVector4() {
	Vector4 vec;

	for (int i = 0; i < 4; ++i) {
		vec[i] = readFloat();
	}

	return vec;
}