/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include <functional>
#include "system/io/ObjectOutputStream.h"
#include "system/io/ObjectInputStream.h"

namespace sys {
  namespace lang {

	class Double : public BaseTypeVariable<double> {
	public:
		Double();

		Double(double val);

		Double(const Double& val);

		Double& operator=(const Double& val);

		bool parseFromString(const String& str, int version = 0);

		bool toString(String& str) const;

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		static float valueOf(const String& str);

		static uint32 hashCode(double value);

	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;
