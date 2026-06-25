/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#pragma once

#include "system/lang.h"
#include "engine/core/Task.h"
#include "engine/log/Logger.h"
#include "engine/util/Singleton.h"
#include "ObjectDatabase.h"
#include "IndexDatabase.h"
#include "berkeley/Environment.h"

//#define LASTOBJECTIDKEY 0xFFFFFFFFFFFFFFFF;

namespace engine {
  namespace db {

	class DatabaseManager;

	class BerkeleyCheckpointTask : public Task {
		DatabaseManager* manager;

	public:
		BerkeleyCheckpointTask(DatabaseManager* manager);

		void run();
	};

	class UpdateObject : public Object {
	public:
		Stream* stream;
		Stream* key;

		engine::db::LocalDatabase* database;

		Reference<Object*> object;

		//if stream null its a delete action

		UpdateObject();

		UpdateObject(Stream* str, Stream* ke, engine::db::LocalDatabase* database, Object* obj);

		UpdateObject(const UpdateObject& i);

		UpdateObject& operator=(const UpdateObject& o);

		uint32 getSize() const;

		int compareTo(const UpdateObject& a) const;

	};

	class CurrentTransaction  {
		Vector<UpdateObject> updateObjects;
		engine::db::berkeley::Environment* databaseEnvironment;


		//stores a references for an object so we dont delete it in the transaction
		Vector<Reference<Object*> > temporaryObjects;

		uint64 currentSize;

	public:
		CurrentTransaction(engine::db::berkeley::Environment* env);

		void addTemporaryObject(Object* obj);

		void clearTemporaryObjects();

		uint32 addUpdateObject(Stream* id, Stream* str, engine::db::LocalDatabase* db, Object* obj);

		uint32 addDeleteObject(Stream* id, engine::db::LocalDatabase* db);

		Vector<UpdateObject>* getUpdateVector();

		uint64 getCurrentSize() const;

		void resetCurrentSize();

	};

	class DatabaseManager : public Logger, public Mutex, public Object {
	protected:
		engine::db::berkeley::Environment* databaseEnvironment = nullptr;

		VectorMap<uint16, LocalDatabase*> databases;
		VectorMap<String, uint16> nameDirectory;

		ThreadLocal<CurrentTransaction*> localTransaction;
		ThreadLocal<engine::db::berkeley::Transaction*> readLocalTransaction;

		LocalDatabase* databaseDirectory = nullptr;

		uint32 dbEnvironmentFlags = 0;

		uint16 lastTableID = 0;
		uint64 currentVersion = 0;

		Reference<BerkeleyCheckpointTask*> checkpointTask;
		uint32 checkpointTime = 0;

		bool loaded = false;

		bool managedObjectsWithHashCodeMembers = true;

	public:
		const static int CHECKPOINTTIME = 1800000; //msec
		const static uint64 LASTOBJECTIDKEY = uint64((uint64)0xFFFFFFFF << 32) + 0xFFFFFFFF;
		const static uint64 VERSIONKEY = uint64((uint64)0xFFFFFFFF << 32) + 0xFFFFFFFE;
		const static uint64 MANAGED_OBJECTS_HASHCODE_MEMBERS = uint64((uint64)0xFFFFFFFF << 32) + 0xFFFFFFFD;
		const static uint64 COMPRESSION_FLAG = 0x80000000;

		static uint64 MAX_CACHE_SIZE; // max in ram cache per thread
		static bool CONVERT_DATABASES;

	private:
		void openEnvironment();
		void closeEnvironment();

	protected:
		LocalDatabase* instantiateDatabase(const String& name, bool create, uint16 uniqueID, LocalDatabase::DatabaseType dbType, bool compression);

	public:
		DatabaseManager();
		~DatabaseManager();

		void loadDatabases(bool truncateDatabases = false);
		void closeDatabases();

		/**
		 * Loads or creates a database in this environment
		 * @param name name of the database
		 * @param create create if no database exists with specified uniqueID/name pair
		 * @param uniqueID if not specified, uniqueID will be set to name.hashCode()
		 */
		LocalDatabase* loadLocalDatabase(const String& name, bool create, uint16 uniqueID = 0xFFFF, bool compression = true,
			       	LocalDatabase::DatabaseType dbType = LocalDatabase::DatabaseType::LOCALDATABASE);

		IndexDatabase* loadIndexDatabase(const String& name, bool create, uint16 uniqueID = 0xFFFF, bool compression = true);

		void checkpoint();

		void getDatabaseName(uint16 tableID, String& name);

		void commitLocalTransaction(engine::db::berkeley::Transaction* transaction = nullptr);
		void startLocalTransaction();
		void abortLocalTransaction();

		int failCheck();

		engine::db::berkeley::Transaction* startTransaction(const engine::db::berkeley::TransactionConfig& config = berkeley::TransactionConfig::DEFAULT);
		int commitTransaction(engine::db::berkeley::Transaction* transaction);
		/**
		 * Stores a references to an object while the transaction is alive
		 * References will be released when the local transaction is commited
		 */
		void addTemporaryObject(Object* object);

		CurrentTransaction* getCurrentTransaction();
		engine::db::berkeley::Transaction* getReadLocalTransaction(bool abortPrevious = false);

		void updateLastUsedObjectID(uint64 id);
		uint64 getLastUsedObjectID();

		void updateCurrentVersion(uint64 version);

		int compressDatabase(const String& name, engine::db::berkeley::Transaction* transaction);

		void setManagedObjectsWithHashCodeMembersFlag(engine::db::berkeley::Transaction* transaction);
		void convertDatabasesToHashCodeMembers();

		uint64 getCurrentVersion() const;

		LocalDatabase* getDatabase(uint16 id) const;

		LocalDatabase* getDatabase(int idx) const;

		uint16 getDatabaseID(const String& name) const;

		int getTotalDatabaseCount() const;

		engine::db::berkeley::Environment* getBerkeleyEnvironment() const;

	};

  } // namespace db
} // namespace engine

using namespace engine::db;
