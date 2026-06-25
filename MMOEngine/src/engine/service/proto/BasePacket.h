/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/service/Message.h"

namespace engine {
  namespace service {
    namespace proto {

	class BasePacket : public Message {
	protected:
		sys::uint32 sequence = 0;
		bool doSeq = true;

		bool doEncr = true;
		bool doComp = false;
		bool doCRCTest = true;

		Time timestamp;
		Time timeout;

		int outOfOrderCount;

	public:
		BasePacket();
		BasePacket(int size);
		BasePacket(const Packet* pack, uint32 seq);

		virtual ~BasePacket() {
		}

		void close();

		BasePacket* clone(int startoffs = 0);

		int compareTo(BasePacket* pack);

		bool isDataChannelPacket();

		bool isMultiPacket();

		// setters
		void setSequence(sys::uint32 seq);

		void setSequencing(bool seq);

		void setEncryption(bool enc);

		void setCompression(bool comp);

		void setCRCChecking(bool crctest);

		void setTimestamp();

		void setTimeout(uint64 time);

		// getters
		sys::uint32 getSequence() const;

		bool doSequencing() const;

		bool doEncryption() const;

		bool doCompression() const;

		bool doCRCChecking() const;

		Time& getTimestamp();

		const Time& getTimestamp() const;

		const Time& getTimeout() const;

		Time& getTimeout();
	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;
