/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * SessionResponseTask.h
 *
 *  Created on: 23/06/2012
 *      Author: victor
 */

#pragma once

class SessionResponseTask : public Task {
	Reference<BaseClient*> client;
	uint32 seed;

public:
	SessionResponseTask(BaseClient* cl, uint32 seed) {
		client = cl;
		this->seed = seed;

#if defined(BASECLIENT_DISABLE_STATSD) and defined(COLLECT_TASKSTATISTICS)
		setStatsSample(0);
#endif
	}

	void run() {
		client->notifyReceivedSeed(seed);
	}
};
