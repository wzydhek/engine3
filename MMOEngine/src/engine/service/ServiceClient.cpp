/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#include "ServiceClient.h"

ServiceClient::ServiceClient() {
	socket = nullptr;

	errored = false;

	packetLossChance = 0;
}

ServiceClient::ServiceClient(Socket* sock) {
	socket = sock;

	errored = false;

	packetLossChance = 0;
}

ServiceClient::ServiceClient(Socket* sock, const SocketAddress& addr) {
	socket = sock;
	ServiceClient::addr = addr;

	errored = false;

	packetLossChance = 0;
}

ServiceClient::ServiceClient(const String& host, int port) {
	setAddress(host, port);

	errored = false;

	packetLossChance = 0;
}

ServiceClient::~ServiceClient() {
	//StackTrace::printStackTrace();
}

void ServiceClient::close() {
	if (socket != nullptr) {
		socket->close();

		delete socket;
		socket = nullptr;
	}
}

bool ServiceClient::isAvailable() {
	if (socket == nullptr)
		return false;

	return !(errored || disconnected);
}

bool ServiceClient::isDisconnected() const {
	return disconnected;
}

bool ServiceClient::hasError() const {
	return errored;
}

void ServiceClient::finalize() {
	release();
}

void ServiceClient::acquire() {
	Object::acquire();
}

void ServiceClient::release() {
	Object::release();
}

void ServiceClient::setHandler(ServiceHandler* handler) {
	serviceHandler = handler;
}

 void ServiceClient::setAddress(const String& host, int port) {
	addr = SocketAddress(host, port);
}

void ServiceClient::setError() {
	errored = true;
}

void ServiceClient::setPacketLoss(int ratio) {
	packetLossChance = ratio;
}

// getters
uint64 ServiceClient::getNetworkID() const {
	return addr.getNetworkID();
}

SocketAddress& ServiceClient::getAddress() {
	return addr;
}

const SocketAddress& ServiceClient::getAddress() const {
	return addr;
}

Socket* ServiceClient::getSocket() {
	return socket;
}

const Socket* ServiceClient::getSocket() const {
	return socket;
}