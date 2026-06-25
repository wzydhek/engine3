#include "UpdateModifiedObjectsTask.h"

UpdateModifiedObjectsTask::UpdateModifiedObjectsTask() {
}

void UpdateModifiedObjectsTask::run() {
	if (DistributedObjectBroker::instance()->isRootBroker())
		DistributedObjectBroker::instance()->getObjectManager()->createBackup();
}