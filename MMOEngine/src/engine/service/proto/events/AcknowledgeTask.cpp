#include "engine/core/Task.h"
#include "engine/service/proto/BaseClient.h"
#include "AcknowledgeTask.h"

AcknowledgeTask::AcknowledgeTask(BaseClient* cl, uint16 sequence) {
	client = cl;
	seq = sequence;

#if defined(BASECLIENT_DISABLE_STATSD) and defined(COLLECT_TASKSTATISTICS)
	setStatsSample(0);
#endif
}

void AcknowledgeTask::run() {
	client->acknowledgeServerPackets(seq);
}