/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * ObserverEventMap.h
 *
 *  Created on: 20/06/2010
 *      Author: victor
 */

#pragma once

namespace engine {
 namespace util {
	 class Observable;
	 class Observer;
} // namespace util
} // namespace engine

using namespace engine::util;

#include "system/lang.h"
#include "engine/core/ManagedReference.h"

namespace engine {
namespace util {

	class ObserverEventMap : public HashTable<uint32, SortedVector<ManagedReference<Observer*>>> {
	mutable ReadWriteLock observerMutex;

public:
	ObserverEventMap();

	ObserverEventMap(const ObserverEventMap& map);

	void notifyObservers(uint32 eventType, Observable* observable, ManagedObject* arg1 = nullptr, int64 arg2 = 0);

	void registerObserver(uint32 eventType, Observer* observer);

	void dropObserver(uint32 eventType, Observer* observer);

	SortedVector<ManagedReference<Observer*> > getObservers(uint32 eventType) const;

	int getObserverCount(uint32 eventType) const;
	int getFullObserverCount() const;
};

}
}

using namespace engine::util;
