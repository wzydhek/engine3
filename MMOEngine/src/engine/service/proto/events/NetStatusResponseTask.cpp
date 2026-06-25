#include "NetStatusResponseTask.h"

NetStatusResponseTask::NetStatusResponseTask(BaseClient* cl, Packet* inPack) {
	client = cl;
	pack = inPack->clone();

#if defined(BASECLIENT_DISABLE_STATSD) and defined(COLLECT_TASKSTATISTICS)
	setStatsSample(0);
#endif
}

NetStatusResponseTask::~NetStatusResponseTask() {
	if (pack != nullptr) {
		delete pack;
	}
}

void NetStatusResponseTask::run() {
	client->handleNetStatusRequest(pack);
	delete pack;
	pack = nullptr;
}