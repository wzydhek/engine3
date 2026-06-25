/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include <functional>
#include "BaseTypeVariable.h"
#include "String.h"
#include "NumberFormatException.h"
#include "system/io/ObjectOutputStream.h"
#include "system/io/ObjectInputStream.h"

namespace sys {
  namespace lang {

	class Float : public BaseTypeVariable<float> {
	public:
		Float();

		Float(float val);

		Float(const Float& val);

		Float& operator=(const Float& val);

		bool parseFromString(const String& str, int version = 0);

		bool toString(String& str) const;

		bool toBinaryStream(sys::io::ObjectOutputStream* stream);

		bool parseFromBinaryStream(sys::io::ObjectInputStream* stream);

		static float valueOf(const String& str);

		static uint32 hashCode(float value);

		static bool areAlmostEqualRelative(float A, float B, float maxRelDiff = FLT_EPSILON);

	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;

