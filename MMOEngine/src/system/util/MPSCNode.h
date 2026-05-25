/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
//
// Created by theanswer on 1/2/18.
//

#pragma once

#include <atomic>

namespace sys {
	namespace util {
			template<typename Data>
			class MPSCNode {
				public:
					MPSCNode(const Data& a) {
						data = a;
					}

					MPSCNode()  = default;
					MPSCNode(MPSCNode<Data>&&)  = default;

					Data data;

					std::atomic<MPSCNode<Data>*> next;
			};
	}
}
