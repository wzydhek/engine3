#include "SessionStartTask.h"
#include "engine/service/proto/packets/SessionIDResponseMessage.h"

SessionStartTask::SessionStartTask(BaseClient* cl, uint32 cid) {
	client = cl;
	connectionID = cid;

#if defined(BASECLIENT_DISABLE_STATSD) and defined(COLLECT_TASKSTATISTICS)
	setStatsSample(0);
#endif
}

void SessionStartTask::run() {
	client->setConnectionID(connectionID);

	Packet* msg = new SessionIDResponseMessage(client);
	client->send(msg);
}