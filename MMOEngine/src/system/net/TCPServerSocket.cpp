#include "TCPServerSocket.h"
#include "SocketException.h"

TCPServerSocket::TCPServerSocket(SocketAddress* addr) : Socket() {
	fileDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (fileDescriptor < 0)
		throw SocketException("unable to create server socket");

	bindTo(addr);
}