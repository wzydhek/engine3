/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "ServiceClient.h"
#include "engine/orb/object/DistributedObject.h"

namespace engine {
  namespace service {

	class Message : public Packet, public Object/*, public DistributedObject */{
	protected:
		Reference<ServiceClient*> client;

		uint64 timestampMili;

	public:
		Message();

		Message(int size);

		Message(const Packet* packet, ServiceClient* clt);

		virtual ~Message() {
		}

		int compareTo(Message* m);

		Message* clone(int startoffs = 0);

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		// setters and getters
		void setClient(ServiceClient* c);

		void setTimeStampMili(uint64 ts);

		uint64 getTimeStampMili() const;

		ServiceClient* getClient() const;

	};

  } // namespace service
} // namespace engine

using namespace engine::service;
