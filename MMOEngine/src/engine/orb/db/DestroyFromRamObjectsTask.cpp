#include "engine/engine.h"
#include "DestroyFromRamObjectsTask.h"

DestroyFromRamObjectsTask::DestroyFromRamObjectsTask(Vector<DistributedObject*>* obj) {
	objects = obj;
}

void DestroyFromRamObjectsTask::run() {
	Logger::console.info("starting to delete " + String::valueOf(objects->size()) + " objects from ram...", true);

	for (int i = 0; i < objects->size(); ++i) {
		objects->get(i)->_destroyIgnoringCount();
	}

	delete objects;
	objects = nullptr;

	Logger::console.info("finished deleting objects from ram", true);
}