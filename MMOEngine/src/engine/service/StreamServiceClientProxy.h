/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "StreamServiceClient.h"

namespace engine {
  namespace service {

	class StreamServiceClientProxy : public StreamServiceClient {
	public:
		StreamServiceClientProxy(Socket* sock) : StreamServiceClient(sock) {
			doRun = true;
		}

		StreamServiceClientProxy(Socket* sock, SocketAddress& addr) : StreamServiceClient(sock, addr) {
			doRun = true;
		}

		virtual ~StreamServiceClientProxy() {
		}

	};

  } // namespace service
} // namespace engine

using namespace engine::service;
