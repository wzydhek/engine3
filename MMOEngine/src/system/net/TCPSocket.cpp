#include "TCPSocket.h"
#include "SocketException.h"

TCPSocket::TCPSocket() : Socket() {
	fileDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fileDescriptor < 0)
		throw SocketException("unable to create socket");
}