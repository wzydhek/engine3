/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Character.h"
#include "Integer.h"
#include "system/io/ObjectOutputStream.h"
#include "system/io/ObjectInputStream.h"

namespace sys {
  namespace lang {

	class Byte : public UnsignedCharacter {
	public:
		Byte();

		Byte(unsigned char val);

		Byte(const Byte& val);

		Byte& operator=(const Byte& b);

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		bool toString(String& str) const;

		bool parseFromString(const String& str, int version = 0);

	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;

