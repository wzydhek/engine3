/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"

namespace engine {
  namespace ORB {

  	class DistributedObjectStub;

  	class DistributedObjectClassHelper;

	class DistributedObjectServant : public Object {
	protected:
		DistributedObjectClassHelper* _classHelper = nullptr;

		WeakReference<DistributedObjectStub*> _stub;

	public:
		DistributedObjectServant();

		virtual ~DistributedObjectServant();

		void setDeployingName(const String& name);

		virtual void _setStub(DistributedObjectStub* stub);

		virtual void _serializationHelperMethod() = 0;

		virtual DistributedObjectStub* _getStub() = 0;

		String toString() const;

		// setters
		void _setClassHelper(DistributedObjectClassHelper* helper);

		// getters
		DistributedObjectClassHelper* _getClassHelper();
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
