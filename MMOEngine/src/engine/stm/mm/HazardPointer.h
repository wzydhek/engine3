/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

namespace engine {
  namespace stm {

	class HazardPointer {
		Vector<Object*> retireList;

		static const int RETIRED_TRESHOLD = 100;

	public:
		void retireObject(Object* object) {
			retireList.add(object);

			if (retireList.size() > RETIRED_TRESHOLD)
				scan();
		}

		void scan() {

		}

	};

  } // namespace stm
} // namespace engine
