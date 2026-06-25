/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/util/Vector.h"

namespace engine {
  namespace stm {

	class HazardPointer {
		Vector<Object*> retireList;

		static const int RETIRED_TRESHOLD = 100;

	public:
		void retireObject(Object* object);

		void scan() {

		}

	};

  } // namespace stm
} // namespace engine

using namespace engine::stm;