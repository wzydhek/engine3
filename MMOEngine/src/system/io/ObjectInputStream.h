/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Stream.h"

#ifndef PLATFORM_WIN
#include <arpa/inet.h>
#else
#include <winsock2.h>
#endif

namespace sys {
  namespace io {

	class ObjectInputStream : public virtual Stream {
	public:
		ObjectInputStream();

		ObjectInputStream(int initsize);

		ObjectInputStream(int initsize, int capincr);

		ObjectInputStream(char *buf, int len);

		virtual ~ObjectInputStream() {
		}

		template<typename T>
		T readPrimitive() {
			constexpr auto typeSize = sizeof(T);

			shiftOffset(typeSize);

			T val;
			memcpy(&val, offset - typeSize, typeSize);

			return val;
		}

		template<typename T>
		T readPrimitiveFrom(int offs) {
			constexpr auto typeSize = sizeof(T);

			auto elementOffset = elementData + offs;

			if (elementOffset + typeSize > end)
				throw StreamIndexOutOfBoundsException(this, offs + typeSize);

			T val;
			memcpy(&val, elementOffset, typeSize);

			return val;
		}

		// reading methods
		bool readBoolean();

		uint8 readByte();

		uint8 readByte(int offs);

		int8 readSignedByte();

		int8 readSignedByte(int offs);

		uint16 readShort();

		uint16 readShort(int offs);

		int16 readSignedShort(int offs);

		int16 readSignedShort();

		uint32 readInt();

		uint32 readNetInt();

		uint32 readInt(int offs);

		int32 readSignedInt();

		int32 readSignedInt(int offs);

		uint64 readLong();

		uint64 readLong(int offs);

		int64 readSignedLong();

		int64 readSignedLong(int offs);

		float readFloat();

		float readFloat(int offs);

		double readDouble();
	};

  } // namespace io
} // namespace sys

using namespace sys::io;
