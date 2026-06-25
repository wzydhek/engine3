#include "BaseClientHealthEvent.h"

BaseClientHealthEvent::BaseClientHealthEvent(BaseClient* client) {
	BaseClientHealthEvent::client = client;

#if defined(BASECLIENT_DISABLE_STATSD) and defined(COLLECT_TASKSTATISTICS)
	setStatsSample(0);
#endif
}

void BaseClientHealthEvent::shutdown() {
	cancel();
	client = nullptr;
}

void BaseClientHealthEvent::run() {
	auto strong = client.get();

	if (strong == nullptr)
		return;

	strong->runHealthCheck();
}