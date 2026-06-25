/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/util/Singleton.h"
#include "DistributedObject.h"
#include "DistributedObjectServant.h"

namespace engine {
  namespace ORB {

	class DistributedObjectStub : public DistributedObject {
	protected:
		Reference<DistributedObjectServant*> _impl;

		bool deployed;

		DistributedObjectClassHelper* _classHelper;

		bool destroyed;

	#ifdef TRACE_REFERENCING
		Vector<StackTrace*> traces;

		StackTrace* finalizedTrace;
	#endif

	public:
		DistributedObjectStub();

		~DistributedObjectStub();

		//virtual DistributedObjectStub* clone();

		// deployment methods
		void deploy();
		void deploy(const char* name);
		void deploy(const String& name);
		void deploy(const String& name, sys::uint64 nid);

		void _requestServant();

		bool undeploy();

		// reference counting methods
		virtual void finalize();

		//virtual void acquire();

		//virtual void release();

		void printReferenceTrace() const;

		// setters
		void setDeployingName(const String& name);

		void _setClassHelper(DistributedObjectClassHelper* helper);

		void setDeployed(bool val);

		virtual void _setImplementation(DistributedObjectServant* impl);

		// getters
		bool isDeployed() const;

		virtual DistributedObjectServant* _getImplementation();

		virtual DistributedObjectServant* _getImplementationForRead() const;

		DistributedObjectClassHelper* _getClassHelper();

		virtual DistributedObjectServant* getServant();
	};

	class DummyConstructorParameter : public Singleton<DummyConstructorParameter>, public Object {
		friend class SingletonWrapper<DummyConstructorParameter>;
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
