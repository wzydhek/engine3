/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * DestroyFromRamObjectsTask.h
 *
 *  Created on: 10/10/2012
 *      Author: victor
 */

#pragma once

namespace engine {
namespace ORB {

class DestroyFromRamObjectsTask : public Task {
	Vector<DistributedObject*>* objects;

public:
	DestroyFromRamObjectsTask(Vector<DistributedObject*>* obj);

	void run();
};

} // namespace ORB
} // namespace engine

using namespace engine::ORB;
