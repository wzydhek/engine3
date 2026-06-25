#include "DistributedObjectAdapter.h"

DistributedObjectAdapter::DistributedObjectAdapter(DistributedObjectStub* obj) {
	// impl = obj;
	stub = nullptr;
}

void DistributedObjectAdapter::setStub(DistributedObjectStub* stb) {
	stub = stb;
}

DistributedObjectStub* DistributedObjectAdapter::getStub() {
	return stub;
}