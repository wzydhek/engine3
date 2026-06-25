/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "engine/log/Logger.h"
#include "Message.h"

namespace engine {
  namespace service {

	class SynchronizedMessageQueue : public ArrayList<Message*> {
		AtomicInteger readIndex, writeIndex;

		bool blocked;

	public:
		SynchronizedMessageQueue(int capacity);

		virtual ~SynchronizedMessageQueue();

		void push(Message* msg);

		Message* pop();

		void flush();

	protected:
		int getBufferSize() const;

	};

  } // namespace service
} // namespace engine

using namespace engine::service;
