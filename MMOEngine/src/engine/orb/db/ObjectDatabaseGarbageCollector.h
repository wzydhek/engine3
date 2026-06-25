/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * ObjectDatabaseGarbageCollector.h
 *
 *  Created on: 13/11/2010
 *      Author: victor
 */

#pragma once

#include "engine/engine.h"

namespace engine {
namespace ORB {

class ObjectDatabaseGarbageCollector : public Task {
public:
	void run();
};

} // namespace ORB
} // namespace engine

using namespace engine::ORB;
