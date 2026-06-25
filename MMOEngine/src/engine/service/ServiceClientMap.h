/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "ServiceClient.h"

namespace engine {
  namespace service {

	class ServiceClientMap : public HashTable<uint64, ServiceClient*>, 
			public HashTableIterator<uint64, ServiceClient*> {
				
		int maxConnections;

	public:
		ServiceClientMap(int maxconn);

		bool add(ServiceClient* client);

		bool remove(ServiceClient* client);
		
	};

  } // namespace service
} // namespace engine

using namespace engine::service;
