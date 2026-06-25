/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * StrongAndWeakReferenceCount.h
 *
 *  Created on: 06/06/2012
 *      Author: victor
 */

#pragma once

#ifdef CXX11_COMPILER
	#include <type_traits>
#endif

#include "system/thread/atomic/AtomicReference.h"
#include "ReferenceCounter.h"

namespace sys {
  namespace lang {

  class Object;

class StrongAndWeakReferenceCount {
protected:
	ReferenceCounter strongReferenceCount;
	ReferenceCounter weakReferenceCount;
	AtomicReference<Object*> object;
public:
	StrongAndWeakReferenceCount(uint32 strongCount, uint32 weakCount, Object* obj);

	StrongAndWeakReferenceCount(const StrongAndWeakReferenceCount& r);

	StrongAndWeakReferenceCount& operator=(const StrongAndWeakReferenceCount& r);

	void markAsDestroyed() volatile;

	uint32 increaseStrongCount() volatile;

	uint32 increaseWeakCount() volatile;

	uint32 decrementAndTestAndSetStrongCount();

	bool tryStrongFinalDecrement();

	uint32 decrementAndTestAndSetWeakCount() volatile;

	void clearStrongCountLowestBit() volatile;

	uint32 getStrongReferenceCount() volatile const;

	void setObject(Object* obj);

	Object* getObject() const;

	void resetCountsToZero();

	template<class R, bool virt>
	class Helper {
	public:
		R static convert(Object* o) {
			return R();
		}
	};

	template<class R>
	class Helper<R, false> {
	public:
		R static convert(Object* o) {
			return static_cast<R>(o);
		}
	};

	template<class R>
	class Helper<R, true> {
	public:
		R static convert(Object* o) {
			return dynamic_cast<R>(o);
		}
	};

	template <class O>
	O getObjectReference() {
#ifdef CXX11_COMPILER
		return Helper<O, std::remove_pointer<O>::type::is_virtual_object>::convert(object.get());
#else
		return dynamic_cast<O>(object.get());
#endif
	}

};

  }
}

using namespace sys::lang;