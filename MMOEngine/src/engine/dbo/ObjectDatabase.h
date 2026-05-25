/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#pragma once

#include "system/lang.h"

namespace engine {
  namespace dbo {

	template <class K, class O> class ObjectDatabase {
	public:
		bool createObject(const K& key, O* object);

		O* getObject(const K& key);

		bool destroyObject(const K& key);
	};

  } // namespace dbo
} // namespace engine
