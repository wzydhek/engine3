/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "DOBMessage.h"
#include "engine/core/Task.h"

namespace engine {
  namespace ORB {

	class InvokeMethodMessage : public DOBMessage {
		uint64 objectID;
		uint32 methodID;
		uint32 invocationID;

		Packet* packet;

	public:	
		InvokeMethodMessage(uint64 objectid, sys::uint32 methid, sys::uint32 invid, bool async);
		InvokeMethodMessage(Packet* message);

		~InvokeMethodMessage();

		void runMethod();

		void execute();

		void handleReply(Packet* resp);

		Packet* getResponseMessage();

		bool getBooleanParameter();

		byte getByteParameter();

		char getSignedCharParameter();

		unsigned char getUnsignedCharParameter();

		int getSignedIntParameter();

		unsigned int getUnsignedIntParameter();

		long long getSignedLongParameter();

		unsigned long long getUnsignedLongParameter();

		short getSignedShortParameter();

		unsigned short getUnsignedShortParameter();

		float getFloatParameter();

		double getDoubleParameter();

		String& getAsciiParameter(String& ascii);

		UnicodeString& getUnicodeParameter(UnicodeString& str);

		Packet* getIncomingPacket();

	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
