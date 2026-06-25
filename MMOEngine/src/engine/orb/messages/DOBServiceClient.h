/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/log/Logger.h"
#include "engine/service/StreamServiceClient.h"
#include "system/util/SynchronizedHashTable.h"
#include "DOBMessage.h"

namespace engine {
  namespace ORB {

	class RemoteObjectBroker;

	class DOBServiceClient : public StreamServiceClient, public Logger {
		RemoteObjectBroker* rob;

		SynchronizedHashTable<uint32, DOBMessage*> sentMessageQueue;
		AtomicInteger sentMessageSequence;

	public:
		DOBServiceClient(Socket* sock);
		DOBServiceClient(const String& host, int port);

		~DOBServiceClient();

		void run();

		void receiveMessages();

		bool send(DOBMessage* message);

		bool sendAndAcceptReply(DOBMessage* message);
		bool sendReply(DOBMessage* message);
		bool sendWithReply(DOBMessage* message);

		bool waitForReply(DOBMessage* message);

		RemoteObjectBroker* getRemoteObjectBroker();

		DOBMessage* getQueuedMessage(uint32 sequence);
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
