#include "UDPSocket.h"
#include "SocketException.h"

UDPSocket::UDPSocket() : Socket() {
	fileDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (fileDescriptor < 0)
		throw SocketException("unable to create socket");
}