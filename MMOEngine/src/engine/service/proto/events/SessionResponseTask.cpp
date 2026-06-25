#include "SessionResponseTask.h"

SessionResponseTask::SessionResponseTask(BaseClient* cl, uint32 seed) {
	client = cl;
	this->seed = seed;

#if defined(BASECLIENT_DISABLE_STATSD) and defined(COLLECT_TASKSTATISTICS)
	setStatsSample(0);
#endif
}

void SessionResponseTask::run() {
	client->notifyReceivedSeed(seed);
}