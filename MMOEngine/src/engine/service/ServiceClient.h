/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"

namespace engine {
  namespace service {

  	class ServiceHandler;

	class ServiceClient : public Object {
	protected:
		ServiceHandler* serviceHandler = nullptr;

		SocketAddress addr;
		Socket* socket = nullptr;

		bool errored = false, disconnected = false;

		int packetLossChance = 0;

	public:
		ServiceClient();
		ServiceClient(Socket* sock);
		ServiceClient(Socket* sock, const SocketAddress& addr);
		ServiceClient(const String& host, int port);

		virtual ~ServiceClient();

		void close();

		virtual int send(Packet* packet) = 0;

		bool isAvailable();

		bool isDisconnected() const;

		bool hasError() const;

		virtual void finalize();

		virtual void acquire();

		virtual void release();

		// setters
		void setHandler(ServiceHandler* handler);

		void setAddress(const String& host, int port);

		void setError();

		void setPacketLoss(int ratio);

		// getters
		uint64 getNetworkID() const;

		SocketAddress& getAddress();

		const SocketAddress& getAddress() const;

		Socket* getSocket();

		const Socket* getSocket() const;
	};

  } // namespace service
} // namespace engine

using namespace engine::service;
