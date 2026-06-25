#include "OutOfOrderTask.h"

OutOfOrderTask::OutOfOrderTask(BaseClient* cl, uint16 sequence) {
	client = cl;
	seq = sequence;

#if defined(BASECLIENT_DISABLE_STATSD) and defined(COLLECT_TASKSTATISTICS)
	setStatsSample(0);
#endif
}

void OutOfOrderTask::run() {
	client->resendPackets(seq);
}