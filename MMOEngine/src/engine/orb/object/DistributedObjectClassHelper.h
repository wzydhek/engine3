/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "DistributedObject.h"
#include "DistributedObjectServant.h"
#include "DistributedObjectAdapter.h"

namespace engine {
  namespace ORB {

	class DistributedObjectStub;
	class DistributedObjectPOD;

	class DistributedObjectClassHelper : public Object {
	protected:
		String className;

	public:
		DistributedObjectClassHelper() {
		}

		virtual ~DistributedObjectClassHelper() {
		}

		virtual void finalizeHelper() = 0;

		virtual DistributedObject* instantiateObject() = 0;

		virtual DistributedObjectServant* instantiateServant() = 0;

		virtual DistributedObjectAdapter* createAdapter(DistributedObjectStub* obj) = 0;

		virtual DistributedObjectPOD* instantiatePOD() = 0;

		const String& getClassName();
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
