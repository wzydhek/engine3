#include "Condition.h"

Condition::Condition() {
	// cmutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&cmutex, nullptr);

	// cond = PTHREAD_COND_INITIALIZER;
	pthread_cond_init(&cond, nullptr);

	signalCount = 0;
	waiterCount = 0;
}

Condition::~Condition() {
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&cmutex);
}

void Condition::init() {
	pthread_cond_init(&cond, nullptr);
}

int Condition::wait(Mutex* m) {
	return doWait(&(m->mutex));
}

int Condition::wait() {
	pthread_mutex_lock(&cmutex);

	int res = doWait(&cmutex);

	pthread_mutex_unlock(&cmutex);
	return res;
}

int Condition::timedWait(Mutex* m, const Time* time) {
	return doTimedWait(&(m->mutex), time);
}

int Condition::timedWait(const Time* time) {
	pthread_mutex_lock(&cmutex);

	int res = doTimedWait(&cmutex, time);

	pthread_mutex_unlock(&cmutex);
	return res;
}

void Condition::signal(Mutex* m) {
	doSignal();
}

void Condition::signal() {
	pthread_mutex_lock(&cmutex);

	doSignal();

	pthread_mutex_unlock(&cmutex);
}

void Condition::broadcast(Mutex* m) {
	doBroadcast();
}

void Condition::broadcast() {
	pthread_mutex_lock(&cmutex);

	doBroadcast();

	pthread_mutex_unlock(&cmutex);
}

int Condition::doWait(pthread_mutex_t* mutex) {
	if (signalCount > 0) {
		--signalCount;

		return 0;
	}

	waiterCount++;

	int res = pthread_cond_wait(&cond, mutex);
	if (res != 0)
		System::out << "outer wait() failed on Condition (" << res << ")\n";

	waiterCount--;

	return res;
}

int Condition::doTimedWait(pthread_mutex_t* mutex, const Time* time) {
	if (signalCount > 0) {
		--signalCount;

		/*struct timespec trem;
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, time->getTimeSpec(), &trem);*/

		return 0;
	}

	waiterCount++;

	int res = pthread_cond_timedwait(&cond, mutex, time->getTimeSpec());

	waiterCount--;

	if (res != 0 && res != ETIMEDOUT) {
		System::out << "timedwait() failed on Condition (" << res << ")\n";
		return res;
	}

	return res;
}

void Condition::doSignal() {
	if (waiterCount == 0) {
		signalCount++;
		return;
	}

	int res = pthread_cond_signal(&cond);
	if (res != 0)
		System::out << "outer signal() failed on Condition (" << res << ")\n";
}

void Condition::doBroadcast() {
	int res = pthread_cond_broadcast(&cond);
	if (res != 0)
		System::out << "outer broadcast() failed on Condition (" << res << ")\n";
}