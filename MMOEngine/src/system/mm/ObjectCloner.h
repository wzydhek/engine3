/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang/Time.h"

namespace sys {
  namespace mm {

   class CloneCounter {
   public:
	   static AtomicInteger cloneCount;
   };

	template <class O> class ObjectCloner {
	public:

		//static uint64 maxTime;

		static Object* clone(O* object) {
			//Time start;

			//CloneCounter::cloneCount.increment();

			Object* o = dynamic_cast<Object*>(new O(*object));

			/*uint64 diff = start.miliDifference();

			if (diff > maxTime)
				maxTime = diff;*/

			return o;
		}
	};

	//template <class O> uint64 ObjectCloner<O>::maxTime = 0;

  } // namespace mm
} // namespace sys
