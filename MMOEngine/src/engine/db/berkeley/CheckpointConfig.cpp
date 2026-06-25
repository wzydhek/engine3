#include "CheckpointConfig.h"

CheckpointConfig::CheckpointConfig() {
	KBytes = 0;
	minutes = 0;
	force = false;
}

void CheckpointConfig::setKBytes(uint32 kbytes) {
	KBytes = kbytes;
}

void CheckpointConfig::setMinutes(uint32 min) {
	minutes = min;
}

void CheckpointConfig::setForce(bool forceCheckpoint) {
	force = forceCheckpoint;
}

uint32 CheckpointConfig::getKBytes() const {
	return KBytes;
}

uint32 CheckpointConfig::getMinutes() const {
	return minutes;
}

bool CheckpointConfig::getForce() const {
	return force;
}