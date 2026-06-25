/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#include "InetAddress.h"

InetAddress::InetAddress(const String& address) {
	ipaddress = address;
}

void InetAddress::setHostName(const String& host) {
	hostname = host;
}

// getters
const String& InetAddress::getHostAddress() const {
	return ipaddress;
}

const String& InetAddress::getHostName() const {
	return hostname;
}