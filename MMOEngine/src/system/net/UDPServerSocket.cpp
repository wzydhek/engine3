#include "UDPServerSocket.h"
#include "SocketException.h"

UDPServerSocket::UDPServerSocket(SocketAddress* addr) : Socket() {
	fileDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (fileDescriptor < 0)
		throw SocketException("unable to create server socket");

	bindTo(addr);
}