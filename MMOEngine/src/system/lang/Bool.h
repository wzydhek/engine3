/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "BaseTypeVariable.h"
#include "system/io/ObjectOutputStream.h"
#include "system/io/ObjectInputStream.h"

namespace sys {
  namespace lang {

	class Bool : public BaseTypeVariable<bool> {
	public:
		Bool();

		Bool(bool val);

		Bool(const Bool& val);

		Bool& operator=(const Bool& val);

		bool toString(String& str) const;

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		bool parseFromString(const String& str, int version = 0);

		static bool valueOf(const String& str);

		static uint32 hashCode(bool value);

	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;

