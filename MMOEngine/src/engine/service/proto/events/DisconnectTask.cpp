
#include "DisconnectTask.h"

DisconnectTask::DisconnectTask(BaseClient* cl) {
	client = cl;

#if defined(BASECLIENT_DISABLE_STATSD) and defined(COLLECT_TASKSTATISTICS)
	setStatsSample(0);
#endif
}

void DisconnectTask::run() {
	client->setClientDisconnected();
	client->disconnect();
}