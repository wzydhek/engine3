/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"

namespace engine {
  namespace ORB {

	class DOBMessage : public Packet {
	protected:
		class DOBServiceClient* client;

		uint32 sequence;

		Condition replyCondition;

		bool async;

	public:
		enum MessageTypes { REPLYMESSAGE,
							CONTROLMESSAGE, STATEUPDATEMESSAGE,
							LOOKUPOBJECTMESSAGE, LOOKUPOBJECTBYIDMESSAGE,
							DEPLOYOBJECTMESSAGE, UNDEPLOYOBJECTMESSAGE,
							INVOKEMETHODMESSAGE,
							LOADPERSISTENTOBJECTMESSAGE, UPDATEPERSISTENTOBJECTMESSAGE,
							GETNEXTFREEOBJECTIDMESSAGE, REQUESTSERVANT, SENDOBJECTDATA };

	public:
		DOBMessage(uint32 messageType);
		DOBMessage(uint32 messageType, uint32 initialBufferSize);
		DOBMessage(Packet* packet);

		~DOBMessage();

		virtual void execute() = 0;

		virtual void handleReply(Packet* response) {
		}

		void signalReply();

		bool waitForReply(uint32 timeout = 10000);

		DOBServiceClient* getClient();

		const DOBServiceClient* getClient() const;

		uint32 getSequence() const;

		void setClient(DOBServiceClient* cli);

		void setSequence(uint32 seq);

		void setSize();

		bool isAsync() const;
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
