/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#pragma once

#include "system/platform.h"

namespace sys {
    namespace io {
        class ObjectOutputStream;
        class ObjectInputStream;
    }
}

using namespace sys::io;

namespace engine {
  namespace core {

      class RunStatistics {
      public:
          uint64 totalRunTime;
          uint64 maxRunTime;
          uint64 totalRunCount;
          uint64 minRunTime;

          int compareTo(const RunStatistics& t) const;

          bool toBinaryStream(ObjectOutputStream* stream);

          bool parseFromBinaryStream(ObjectInputStream* stream);
      };

      class RunStatisticsOrderedByMaxTime {
      public:
          uint64 totalRunTime;
          uint64 maxRunTime;
          uint64 totalRunCount;
          uint64 minRunTime;

          RunStatisticsOrderedByMaxTime() = default;
          RunStatisticsOrderedByMaxTime(const RunStatisticsOrderedByMaxTime&) = default;

          RunStatisticsOrderedByMaxTime(const RunStatistics& r);

          int compareTo(const RunStatisticsOrderedByMaxTime& t) const;

          bool toBinaryStream(ObjectOutputStream* stream);

          bool parseFromBinaryStream(ObjectInputStream* stream);
      };

  } // namespace core
} // namespace engine

using namespace engine::core;
