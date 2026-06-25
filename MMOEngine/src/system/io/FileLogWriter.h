/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "FileWriter.h"
#include "system/util/VectorMap.h"
#include "system/lang/ref/Reference.h"
#include <mutex>

namespace sys {
namespace io {
	class FileLogWriter : public FileWriter {
	private:
		bool doSynchronized = false;
		mutable Mutex writeMutex;
		mutable Mutex rotateMutex;
		mutable AtomicInteger currentLoggedBytes;
		uint32 maxLoggedBytes = 0;
		String rotatePrefix = "zArchive/"; // Default to {dir}/zArchive/{filename}

		FileLogWriter(File* file, bool append = false, bool rotateAtStart = false);
		~FileLogWriter();

		void close() override;

	public:
		static Reference<FileLogWriter*> getWriter(const String& fileName, bool append = false, bool rotateAtStart = false);

		void setSynchronized(bool synchronized);

		void setRotateSizeMB(uint32 maxSizeMB);

		void setRotatePrefix(String prefix);

		void closeLog(bool force = false);
		int write(const char* str, int len) override;
		void rotatefile(bool force = false) const;

		const String getFileName() const;
	};
} // namespace io
} // namespace sys

using namespace sys::io;
