/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include <atomic>
#include "DistributedObjectPOD.h"

namespace engine {
  namespace ORB {

	class ObjectBroker;

	class DistributedObjectAdapter;
	class DistributedObjectStub;

	class DistributedObject : public ReadWriteLock, public Object {
	protected:
		String _className;
		String _name;

		uint64 _objectID;

		ObjectBroker* _objectBroker;

		class UpdatedHelper {
		public:
			DistributedObject* obj = nullptr;
			std::atomic<bool> _updated{true};
			AtomicReference<StackTrace*> lastModifiedTrace = nullptr;

			~UpdatedHelper();

			explicit operator bool() const {
				return _updated.load(std::memory_order_relaxed);
			}

			UpdatedHelper& operator=(bool val);

			void clearTrace();
		};

		class DeleteHelper {
		public:
			DistributedObject* obj = nullptr;
			std::atomic<bool> _delete{false};

			explicit operator bool() const {
				return _delete.load(std::memory_order_relaxed);
			}

			DeleteHelper& operator=(bool val);
		};

		UpdatedHelper _updated;
		DeleteHelper _markedForDeletion;
		bool _deletedFromDatabase;

	public:
		DistributedObject();

		virtual ~DistributedObject();

		virtual bool isPersistent() const {
  		    return false;
		}

		// setters
		void _setClassName(const String& n);

		void _setName(const String& n);

		void _setClassName(String&& n);

		void _setName(String&& n);

		void _setObjectID(uint64 id);

		void _setUpdated(bool var);

		void _setDeletedFromDatabase(bool val);

		void _setMarkedForDeletion(bool var);

		void _setObjectBroker(ObjectBroker* broker);

		// getters
		const String& _getClassName() const;

		bool _isDeletedFromDatabase() const;

		const String& _getName() const;

		uint64 _getObjectID() const;

		ObjectBroker* _getObjectBroker() const;

		bool _isUpdated() const;

		bool _isMarkedForDeletion() const;

		const StackTrace* getLastModifiedTrace() const;
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
