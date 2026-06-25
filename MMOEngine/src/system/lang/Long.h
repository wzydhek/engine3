/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include <cstdlib>
#include "Integer.h"
#include "String.h"
#include "StringBuffer.h"
#include "NumberFormatException.h"
#include "BaseTypeVariable.h"
#include "system/io/ObjectOutputStream.h"
#include "system/io/ObjectInputStream.h"

namespace sys {
  namespace lang {

	  class Long : public BaseTypeVariable<int64> {
	  public:
		  Long();

		  Long(int64 val);

		  Long(const Long& val);

		  Long& operator=(const Long& val);

		  bool toString(String& str) const;

		  bool parseFromString(const String& str, int version = 0);

		  bool toBinaryStream(ObjectOutputStream* stream);

		  bool parseFromBinaryStream(ObjectInputStream* stream);

		  static uint32 hashCode(uint64 value);

		  static int64 valueOf(const String& str);

		  static uint64 unsignedvalueOf(const String& str);

		  static String toString(int64 val);

		  static void toString(String& str, int64 val);

		  static String toString(uint64 val);

		  static void toString(String& str, uint64 val);
	  };

	  class UnsignedLong : public BaseTypeVariable<uint64> {
	  public:
		  UnsignedLong();

		  UnsignedLong(uint64 val);

		  UnsignedLong(const UnsignedLong& val);

		  UnsignedLong& operator=(const UnsignedLong& val);

		  bool toString(String& str) const;

		  bool parseFromString(const String& str, int version = 0);

		  bool toBinaryStream(ObjectOutputStream* stream);

		  bool parseFromBinaryStream(ObjectInputStream* stream);

		  static uint64 hexvalueOf(const String& str);

		  static uint64 valueOf(const String& str);

		  static uint32 hashCode(int64 value);
	  };

  } // namespace lang
} // namespace sys

using namespace sys::lang;
