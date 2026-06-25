#include "BaseClientEvent.h"

BaseClientEvent::BaseClientEvent(BaseClient* cl) {
	client = cl;

#if defined(BASECLIENT_DISABLE_STATSD) and defined(COLLECT_TASKSTATISTICS)
	setStatsSample(0);
#endif
}

void BaseClientEvent::run() {
	Reference<BaseClient*> strong = client.get();

	if (strong == nullptr)
		return;

	strong->run();
}