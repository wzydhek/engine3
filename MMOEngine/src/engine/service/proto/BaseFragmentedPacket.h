/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "BasePacket.h"

namespace engine {
  namespace service {
    namespace proto {

	class FragmentedPacketParseException : public Exception {
	public:
		FragmentedPacketParseException(const String& msg);
	};

	class BaseFragmentedPacket : public BasePacket {
		BasePacket* singlePacket;

		int totalSize;

		StringBuffer error;

		StringBuffer& addError();

	public:
		BaseFragmentedPacket();
		BaseFragmentedPacket(BasePacket* pack);

		~BaseFragmentedPacket();

		bool addFragment(Packet* pack);

		BasePacket* getFragment();

		bool isComplete();

		bool hasFragments() const;

		bool hasError() const;

		String getError() const;
	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;
