/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#pragma once

#include "system/platform.h"
#include "BaseTypeVariable.h"
#include "String.h"
#include "system/io/ObjectOutputStream.h"
#include "system/io/ObjectInputStream.h"

namespace sys {
  namespace lang {

	class Character : public BaseTypeVariable<char> {
	public:
		Character();

		Character(char val);

		Character(const Character& val);

		Character& operator=(const Character& val);

		bool toString(String& str) const;

		bool parseFromString(const String& str, int version = 0);

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		static char valueOf(const String& str);

		static bool isDigit(char ch);

		static bool isLetter(char ch);

		static bool isLetterOrDigit(char ch);

		static bool isLowerCase(char ch);

		static bool isUpperCase(char ch);

		static char toLowerCase(char ch);

		static char toUpperCase(char ch);

		static uint32 hashCode(char value);

	};

	class UnsignedCharacter : public BaseTypeVariable<unsigned char> {
	public:
		UnsignedCharacter();

		UnsignedCharacter(unsigned char val);

		UnsignedCharacter(const UnsignedCharacter& val);

		UnsignedCharacter& operator=(const UnsignedCharacter& val);

		bool toString(String& str) const;

		bool parseFromString(const String& str, int version = 0);

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		static uint32 hashCode(unsigned char value);

	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;

