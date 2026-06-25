#include "BaseClientNetStatusCheckupEvent.h"

BaseClientNetStatusCheckupEvent::BaseClientNetStatusCheckupEvent(BaseClient* cl) : Task(25000) {
	client = cl;

#if defined(BASECLIENT_DISABLE_STATSD) and defined(COLLECT_TASKSTATISTICS)
	setStatsSample(0);
#endif
}

void BaseClientNetStatusCheckupEvent::run() {
	Locker locker(&lock);

	auto strongRef = client;

	if (strongRef != nullptr) {
		strongRef->checkNetStatus();
	}
}

void BaseClientNetStatusCheckupEvent::clearClient() {
	Locker locker(&lock);

	client = nullptr;
}