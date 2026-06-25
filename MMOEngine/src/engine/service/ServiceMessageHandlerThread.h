/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "ServiceThread.h"
#include "ServiceClientMap.h"
#include "ServiceHandler.h"
#include "ServiceFilter.h"
#include "MessageQueue.h"

namespace engine {
  namespace service {

	class ServiceMessageHandlerThread : public ServiceThread {
	protected:
		ServiceClientMap* clients;

		Socket* socket;
		int port = 0;

		MessageQueue messageQueue;

		ServiceHandler* serviceHandler;

		ServiceFilter* serviceFilter;

	public:
		ServiceMessageHandlerThread(const String& s);

		virtual ~ServiceMessageHandlerThread();

		bool removeConnection(ServiceClient* client);

		void removeConnections();

		// message functions
		void addMessage(Message* msg);

		Message* getMessage();

		void flushMessages();

		// getters
		MessageQueue* getMessageQueue();

		int getServicePort() const;

		Socket* getSocket() const;

		// setters
		void setHandler(ServiceHandler* handler);

		void setFilter(ServiceFilter* filter);
	};

  } // namespace service
} // namespace engine

using namespace engine::service;
