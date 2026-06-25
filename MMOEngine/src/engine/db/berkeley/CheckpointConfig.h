/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * CheckpointConfig.h
 *
 *  Created on: 15/02/2010
 *      Author: victor
 */

#pragma once

#include "system/lang.h"

namespace engine {
  namespace db {
    namespace berkeley {

	class CheckpointConfig {
		uint32 KBytes;
		uint32 minutes;
		bool force;

	public:
		static CheckpointConfig DEFAULT;

	public:
		CheckpointConfig();

		void setKBytes(uint32 kbytes);

		void setMinutes(uint32 min);

		void setForce(bool forceCheckpoint);

		uint32 getKBytes() const;

		uint32 getMinutes() const;

		bool getForce() const;
	};

    } // namespace berkeley
  } // namespace db
} // namespace engine

using namespace engine::db::berkeley;
