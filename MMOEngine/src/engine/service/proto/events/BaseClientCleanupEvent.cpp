#include "BaseClientCleanupEvent.h"

BaseClientCleanupEvent::BaseClientCleanupEvent(BaseClient* cl) : Task(60000) {
	client = cl;

#if defined(BASECLIENT_DISABLE_STATSD) and defined(COLLECT_TASKSTATISTICS)
	setStatsSample(0);
#endif
}

void BaseClientCleanupEvent::run() {
	client = nullptr;
}