/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include <atomic>
#include "system/lang/ref/ReferenceCounter.h"
//#include "system/lang/ref/WeakReference.h"
#include "system/lang/ref/StrongAndWeakReferenceCount.h"
#include "system/thread/Mutex.h"
#include "system/util/ArrayList.h"
#include "system/thread/atomic/AtomicBoolean.h"
#include "system/thread/atomic/AtomicReference.h"
#include "Variable.h"

#ifdef MEMORY_PROTECTION
#define REFERENCED_WEAK_MUTEX
#endif

//#define TRACE_REFERENCES

namespace engine {
        namespace stm {
                class TransactionalMemoryManager;
        }
}

namespace sys {
	namespace mm {
		class MemoryManager;
	}

	namespace io {
		class ObjectOutputStream;
		class ObjectInputStream;
	}

	namespace util {
		template<class E> class HashSet;
		template<class K, class V, bool RawCopyAndRealloc> class VectorMap;
	}
}

namespace sys {
  namespace lang {

    class String;
    template<class O> class WeakReference;

	using namespace sys::io;
	using namespace sys::util;

	class Object : public Variable {
		mutable AtomicReference<StrongAndWeakReferenceCount*> referenceCounters;

#ifdef MEMORY_PROTECTION
		AtomicBoolean* _destroying;
#endif

	#ifdef TRACE_REFERENCES
		mutable Mutex referenceMutex;
		mutable sys::util::VectorMap<uint64, StackTrace*, true>* referenceHolders;
	#endif

	public:
		constexpr const static bool is_virtual_object = false;
	public:

		Object();
		Object(const Object& obj);

#ifdef CXX11_COMPILER
		Object(Object&& o);

		Object& operator=(Object&& o);
#endif

		~Object();

		Object& operator=(const Object& o);

		virtual Object* clone();

		virtual Object* clone(void* object);

		virtual int compareTo(Object* object);

		virtual bool notifyDestroy();

		void finalize() {
		}

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		void createStrongAndWeakReferenceCount() const;

		void acquire() const;

		bool release() const;

		bool tryFinalRelease() const;

		void _destroyIgnoringCount();

		void _markAsDestroyed();

		uint32 getReferenceCount();

		StrongAndWeakReferenceCount* requestWeak();

		virtual String toString() const;

	#ifdef TRACE_REFERENCES
		void addHolder(uint64 obj) const;
		void removeHolder(uint64 obj) const;

		void printReferenceHolders() const;
	#endif

	protected:
		virtual void destroy();
		virtual void free();

		friend class sys::mm::MemoryManager;
		friend class WeakReference<Object*>;
		friend class engine::stm::TransactionalMemoryManager;
	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;
