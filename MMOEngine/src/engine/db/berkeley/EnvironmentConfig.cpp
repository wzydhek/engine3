#include "EnvironmentConfig.h"

EnvironmentConfig::EnvironmentConfig() {
	environmentFlags = 0;
	threadCount = 0;
	logAutoRemove = false;
	lockDetectMode = LockDetectMode::DEFAULT;
	maxLogFileSize = 10000; // 10mb
}

void EnvironmentConfig::setRegister(bool val) {
	if (!val)
		environmentFlags &= ~DB_REGISTER;
	else
		environmentFlags |= DB_REGISTER;
}

void EnvironmentConfig::setLockDown(bool lockDownToMemory) {
	if (!lockDownToMemory)
		environmentFlags &= ~DB_LOCKDOWN;
	else
		environmentFlags |= DB_LOCKDOWN;
}

void EnvironmentConfig::setAllowCreate(bool allowCreate) {
	if (!allowCreate)
		environmentFlags &= ~DB_CREATE;
	else
		environmentFlags |= DB_CREATE;
}

void EnvironmentConfig::setInitializeLocking(bool initializeLocking) {
	if (!initializeLocking)
		environmentFlags &= ~DB_INIT_LOCK;
	else
		environmentFlags |= DB_INIT_LOCK;
}

void EnvironmentConfig::setInitializeLogging(bool initializeLogging) {
	if (!initializeLogging)
		environmentFlags &= ~DB_INIT_LOG;
	else
		environmentFlags |= DB_INIT_LOG;
}

void EnvironmentConfig::setRecover(bool recover) {
	if (!recover)
		environmentFlags &= ~DB_RECOVER;
	else
		environmentFlags |= DB_RECOVER;
}

void EnvironmentConfig::setPrivate(bool val) {
	if (!val)
		environmentFlags &= ~DB_PRIVATE;
	else
		environmentFlags |= DB_PRIVATE;
}

void EnvironmentConfig::setLogAutoRemove(bool logAutoRemove) {
	this->logAutoRemove = logAutoRemove;
}

void EnvironmentConfig::setMaxLogFileSize(int maxLogFileSize) {
	this->maxLogFileSize = maxLogFileSize;
}

void EnvironmentConfig::setThreaded(bool threaded) {
	if (!threaded)
		environmentFlags &= ~DB_THREAD;
	else
		environmentFlags |= DB_THREAD;
}

void EnvironmentConfig::setLockDetectMode(uint32 mode) {
	lockDetectMode = mode;
}

void EnvironmentConfig::setThreadCount(int count) {
	threadCount = count;
}

void EnvironmentConfig::setTransactional(bool transactional) {
	if (!transactional)
		environmentFlags &= ~DB_INIT_TXN;
	else
		environmentFlags |= DB_INIT_TXN;
}

void EnvironmentConfig::setInitializeCache(bool initializeCache) {
	if (!initializeCache)
		environmentFlags &= ~DB_INIT_MPOOL;
	else
		environmentFlags |= DB_INIT_MPOOL;
}

void EnvironmentConfig::setMultiVersionConcurrencyControl(bool val) {
	mvcc = val;
}

void EnvironmentConfig::setDirectAccess(bool val) {
	direct = val;
}

bool EnvironmentConfig::isThreaded() const {
	return environmentFlags & DB_THREAD;
}

uint32 EnvironmentConfig::getEnvironmentFlags() const {
	return environmentFlags;
}

uint32 EnvironmentConfig::getThreadCount() const {
	return threadCount;
}

uint32 EnvironmentConfig::getLockDetectMode() const {
	return lockDetectMode;
}

int EnvironmentConfig::getMaxLogFileSize() const {
	return maxLogFileSize;
}

bool EnvironmentConfig::getLogAutoRemove() const {
	return logAutoRemove;
}

bool EnvironmentConfig::isDirectAccess() const {
	return direct;
}

bool EnvironmentConfig::isMVCC() const {
	return mvcc;
}