/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "DistributedObjectStub.h"
#include "engine/orb/messages/DOBMessage.h"

namespace engine {
  namespace ORB {

	class DistributedMethod;

	class DistributedObjectServant;
	
	class DistributedObjectAdapter {
	protected:
		//DistributedObjectServant* impl;

		DistributedObjectStub* stub;

		
	public:
		DistributedObjectAdapter(DistributedObjectStub* obj);
		
		virtual ~DistributedObjectAdapter() {
		}
		
		virtual void invokeMethod(sys::uint32 methid, DistributedMethod* inv) = 0;
		
		void setStub(DistributedObjectStub* stb);
		
		/*inline DistributedObjectServant* getImplementation() {
			return impl;
		}*/
	
		DistributedObjectStub* getStub();
	
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
