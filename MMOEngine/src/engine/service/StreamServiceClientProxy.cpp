#include "system/net/Socket.h"
#include "StreamServiceClientProxy.h"

StreamServiceClientProxy::StreamServiceClientProxy(Socket* sock) : StreamServiceClient(sock) {
	doRun = true;
}

StreamServiceClientProxy::StreamServiceClientProxy(Socket* sock, SocketAddress& addr) : StreamServiceClient(sock, addr) {
	doRun = true;
}