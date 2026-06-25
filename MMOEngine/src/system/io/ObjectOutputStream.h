/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Stream.h"

namespace sys {
  namespace io {

	class ObjectOutputStream : public virtual Stream {
	public:
		ObjectOutputStream();

		ObjectOutputStream(int initsize);

		ObjectOutputStream(int initsize, int capincr);

		ObjectOutputStream(char* buf, int len);

		virtual ~ObjectOutputStream() {
		}

		template<typename T>
		void writePrimitive(const T& val) {
			constexpr auto typeSize = sizeof(T);

			extendSize(typeSize);

			memcpy(offset - typeSize, &val, typeSize);
		}

		template<typename T>
		void writePrimitiveTo(int offs, const T& val) {
			constexpr auto typeSize = sizeof(T);

			char* elementOffset = elementData + offs;
			if (elementOffset + typeSize > end)
				throw StreamIndexOutOfBoundsException(this, offs);

			memcpy(elementOffset, &val, typeSize);
		}

		// writing methods
		void writeBoolean(bool val);

		void writeByte(uint8 val);

		void writeByte(int offs, uint8 val);

		void writeSignedByte(int8 val);

		void writeShort(uint16 val);

		void writeSignedShort(int16 val);

		void writeShort(int offs, uint16 val);

		void writeInt(uint32 val);

		void writeInt(int offs, uint32 val);

		void writeSignedInt(int32 val);

		void writeLong(uint64 val);

		void writeLong(int offs, uint64 val);

		void writeSignedLong(int64 val);

		void writeFloat(float val);

		void writeDouble(double val);
	};

  } // namespace io
} // namespace sys

using namespace sys::io;
