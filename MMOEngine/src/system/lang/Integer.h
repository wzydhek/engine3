/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#pragma once

#include "String.h"
#include "BaseTypeVariable.h"

namespace sys {
  namespace lang {

	class Integer : public BaseTypeVariable<int> {
	public:
		Integer();

		Integer(int val);

		Integer(const Integer& val);

		Integer& operator=(const Integer& val);

		bool toString(String& str) const;

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromString(const String& str, int version = 0);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		static void toBinaryStream(int val, ObjectOutputStream* stream);
		static void parseFromBinaryStream(int& val, ObjectInputStream* stream);

		static int valueOf(char ch);

		static int valueOf(const char* str);

		static int valueOf(const String& str);

		static uint32 hexvalueOf(const String& str);

		static uint32 hashCode(int value);

	};

	class UnsignedInteger: public BaseTypeVariable<uint32> {
	public:
		inline UnsignedInteger();

		inline UnsignedInteger(uint32 val);

		inline UnsignedInteger(const UnsignedInteger& val);

		bool toString(String& str) const;

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromString(const String& str, int version = 0);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		static unsigned int valueOf(const String& str);

		static uint32 hashCode(uint32 value);

	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;
