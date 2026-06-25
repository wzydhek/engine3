/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * DatabaseEntry.h
 *
 *  Created on: 14/02/2010
 *      Author: victor
 */

#pragma once

#include <db.h>
#include "system/platform.h"
#include "system/io/Stream.h"

namespace engine {
  namespace db {
    namespace berkeley {

	class DatabaseEntry {
	protected:
		DBT databaseEntry; //BDB

	public:
		/**
		 *  Construct a DatabaseEntry with null data.
		 */
		DatabaseEntry();

		/**
		 * deletes from memory databaseEntyr.data if setUserBuffer(false)
		 */
		~DatabaseEntry();

		/**
		 * Construct a DatabaseEntry with a given byte array
		 */
		DatabaseEntry(uint8* data, int size);

		/**
		 * Constructs a DatabaseEntry with a given byte array, offset and size
		 */
		//DatabaseEntry(byte* data, int offset, int size);

		/**
		 * Construct a DatabaseEntry with a given native I/O buffer
		 */
		DatabaseEntry(Stream* data);

		/**
		 * Configures the entry with an application-owned buffer.
		 */
		void setUserBuffer(int length, bool usermem);

		/*
		 * Configures the entry to try to reuse the buffer before allocating a new one.
		 */
		void setReuseBuffer(bool reuse);

		/**
		 * Sets the user buffer and size
		 */
		void setData(void* addr, int size);

		void* getData();

		int getSize();

		DBT* getDBT();
	};

    } // namespace berkeley
  } // namespace db
} // namespace engine

using namespace engine::db::berkeley;
