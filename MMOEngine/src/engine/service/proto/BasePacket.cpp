/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#include "BasePacket.h"

BasePacket::BasePacket() : Message() {
	doSeq = true;

	doEncr = true;
	doComp = false;
	doCRCTest = true;

	outOfOrderCount = 0;
}

BasePacket::BasePacket(int size) : Message(size) {
	if (size < 0)
		throw PacketIndexOutOfBoundsException(this, size);

	doSeq = true;

	doEncr = true;
	doComp = false;
	doCRCTest = true;

	outOfOrderCount = 0;
}

BasePacket::BasePacket(const Packet* pack, uint32 seq) : Message(pack->size()) {
	pack->copy(this);

	setOffset(pack->getOffset());

	doSeq = true;
	sequence = seq;

	outOfOrderCount = 0;
}

BasePacket* BasePacket::clone(int startoffs) {
	BasePacket* pack = new BasePacket(elementCount - startoffs);
	copy(pack, startoffs);

	pack->doSeq = doSeq;
	pack->doEncr = doEncr;
	pack->doComp = doComp;
	pack->doCRCTest = doCRCTest;

	return pack;
}

int BasePacket::compareTo(BasePacket* pack) {
	if (sequence < pack->sequence)
		return 1;
	else if (sequence > pack->sequence)
		return -1;
	else
		return 0;
}

void BasePacket::close() {
	if (size() < 100)
		insertByte(doComp = false);
	else
		insertByte(doComp);

	insertByte(0x00);
	insertByte(0x00);
}

bool BasePacket::isDataChannelPacket() {
	if (parseShort(0) == 0x0900)
		return true;
	else
		return false;
}

bool BasePacket::isMultiPacket() {
	if (parseShort(0) == 0x0300 || parseShort(4) == 0x1900)
		return true;
	else
		return false;
}

// setters
void BasePacket::setSequence(sys::uint32 seq) {
	insertShort(2, htons((sys::uint16)(sequence = seq)));
}

void BasePacket::setSequencing(bool seq) {
	doSeq = seq;
}

void BasePacket::setEncryption(bool enc) {
	doEncr = enc;
}

void BasePacket::setCompression(bool comp) {
	doComp = comp;
}

void BasePacket::setCRCChecking(bool crctest) {
	doCRCTest = crctest;
}

void BasePacket::setTimestamp() {
	timestamp.updateToCurrentTime();
}

void BasePacket::setTimeout(uint64 time) {
	timeout.updateToCurrentTime();
	timeout.addMiliTime(time);
}

// getters
sys::uint32 BasePacket::getSequence() const {
	if (doSeq)
		return sequence;
	else
		return 0xFFFFFFFF;
}

bool BasePacket::doSequencing() const {
	return doSeq;
}

bool BasePacket::doEncryption() const {
	return doEncr;
}

bool BasePacket::doCompression() const {
	return doComp;
}

bool BasePacket::doCRCChecking() const {
	return doCRCTest;
}

Time& BasePacket::getTimestamp() {
	return timestamp;
}

const Time& BasePacket::getTimestamp() const {
	return timestamp;
}

const Time& BasePacket::getTimeout() const {
	return timeout;
}

Time& BasePacket::getTimeout() {
	return timeout;
}