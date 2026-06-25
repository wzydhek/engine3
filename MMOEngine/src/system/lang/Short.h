/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "BaseTypeVariable.h"
#include "String.h"
#include "Integer.h"
#include "system/io/ObjectOutputStream.h"
#include "system/io/ObjectInputStream.h"

namespace sys {
  namespace lang {

	class Short : public BaseTypeVariable<int16> {
	public:
		Short();

		Short(int16 val);

		Short(const Short& val);

		Short& operator=(const Short& val);

		bool parseFromString(const String& str, int version = 0);

		bool toString(String& str) const;

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		static uint32 hashCode(int16 value);

	};

	class UnsignedShort : public BaseTypeVariable<uint16> {
	public:
		UnsignedShort();

		UnsignedShort(uint16 val);

		UnsignedShort& operator=(const UnsignedShort& val);

		bool parseFromString(const String& str, int version = 0);

		bool toString(String& str) const;

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		static uint32 hashCode(uint16 value);

	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;
