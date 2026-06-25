/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "engine/util/u3d/Matrix4.h"
#include "engine/util/u3d/Vector3.h"
#include "engine/util/u3d/Vector4.h"

namespace engine {
 namespace util {

	class IffStream;

	class Chunk : public ObjectInputStream {
	protected:
		IffStream* iffStream;
		Chunk* parent;

		uint32 chunkID;
		int chunkSize;

		Vector<Chunk*> subChunks;
		int lastOpenedSubChunk;

	public:
		const static uint32 FORM =  0x464F524D; //'FORM';
		const static uint32 DATA =  0x44415441; //'DATA';
		const static uint32 LIST = 0x4C495354; //'LIST';
		const static uint32 CAT = 0x43415420; //'CAT ';

	public:
		Chunk(Chunk* par, uint32 id, uint32 size, char* data);
		virtual ~Chunk();

		virtual void parseData();

		void setIffStream(IffStream* iff);

		IffStream* getIffStream();

		void setLastOpenedSubChunk(int value);

		void getChildren(Vector<Chunk*>& child);

		bool isFORM();

		bool isDATA();

		Chunk* getParent();

		void addChunk(Chunk* chunk);

		Chunk* getChunk(int idx);

		Chunk* getNextChunk();

		uint32 getChunksSize();

		int getLastOpenedChunkIdx();

		uint32 getChunkID();

		int getChunkSize();

		void readString(String& str);

		String readString();

		Matrix4 readMatrix3x4Transform();

		Vector3 readVector3();

		Vector4 readVector4();

	};

 }
}

using namespace engine::util;
