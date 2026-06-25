#include "BaseClientNetStatusRequestEvent.h"

BaseClientNetStatusRequestEvent::BaseClientNetStatusRequestEvent(BaseClient* cl) : Task(5000) {
	client = cl;

#if defined(BASECLIENT_DISABLE_STATSD) and defined(COLLECT_TASKSTATISTICS)
	setStatsSample(0);
#endif
}

void BaseClientNetStatusRequestEvent::run() {
	Locker locker(&lock);

	auto strongRef = client;

	if (strongRef != nullptr)
		strongRef->requestNetStatus();
}

void BaseClientNetStatusRequestEvent::clearClient() {
	Locker locker(&lock);

	client = nullptr;
}