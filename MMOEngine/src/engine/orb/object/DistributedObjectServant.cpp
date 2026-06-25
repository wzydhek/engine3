/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#include "engine/orb/DistributedObjectBroker.h"

DistributedObjectServant::DistributedObjectServant() {
}

DistributedObjectServant::~DistributedObjectServant() {
}

void DistributedObjectServant::setDeployingName(const String& name) {
	_stub.get()->_setName(name);
}

String DistributedObjectServant::toString() const {
	return _stub.get()->_getName();
}

void DistributedObjectServant::_setStub(DistributedObjectStub* stub) {
	_stub = stub;
}

// setters
void DistributedObjectServant::_setClassHelper(DistributedObjectClassHelper* helper) {
	_classHelper = helper;
}

// getters
DistributedObjectClassHelper* DistributedObjectServant::_getClassHelper() {
	return _classHelper;
}