/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#ifdef NDEBUG
	#define E3_INFO(x)
	#define E3_DEBUG(x)
	#define E3_WARNING(x)
	#define E3_ERROR(x) error(x)
	#define E3_LOG(x) log(x)
	#define E3_FATAL(x) fatal(x)
#else
	#define E3_INFO(x) info(x)
	#define E3_DEBUG(x) debug(x)
	#define E3_WARNING(x) warning(x)
	#define E3_ERROR(x) error(x)
	#define E3_LOG(x) log(x)
	#define E3_FATAL(x) fatal(x)
#endif

#include "system/lang.h"
#include "system/lang/Function.h"
#include "system/thread/Mutex.h"

namespace engine {
  namespace log {

	class Logger;

	template <typename T>
	class HasToStringDataMethodSFINAE {
		typedef char success;
		struct failure { char x[2]; };

		template <class C> static success test(decltype(&C::toStringData)) ;
		template <class C> static failure test(...);

	public:
		enum { value = sizeof(test<T>(0)) == sizeof(char) };
	};

	template <typename T>
	class HasTo_StringMethodSFINAE {
		typedef char success;
		struct failure { char x[2]; };

		template <class C> static success test(decltype(&C::to_string)) ;
		template <class C> static failure test(...);

	public:
		enum { value = sizeof(test<T>(0)) == sizeof(char) };
	};

	class LoggerHelper {
	protected:
		const Logger& logger;
		const int logLevel;
		const bool boolParam;
		bool willLog;

		StringBuffer buffer;

	public:
		LoggerHelper() = delete;

		LoggerHelper(const Logger& logger, const int logLevel, const bool boolParam);
		LoggerHelper(LoggerHelper&& loggerHelper);

		~LoggerHelper();

		void flush(bool clearBuffer = true);

		template<typename T, std::enable_if_t<HasToStringDataMethodSFINAE<T>::value, int> = 0>
		LoggerHelper& operator<<(const T& a) {
			if (!willLog) {
				return *this;
			}

			buffer << a.toStringData();

			return *this;
		}

		template<typename T, std::enable_if_t<HasTo_StringMethodSFINAE<T>::value, int> = 0>
		LoggerHelper& operator<<(const T& a) {
			if (!willLog) {
				return *this;
			}

			buffer << a.to_string();

			return *this;
		}

		template<typename T, std::enable_if_t<!HasToStringDataMethodSFINAE<T>::value
			&& !HasTo_StringMethodSFINAE<T>::value, int> = 0>
		LoggerHelper& operator<<(const T& a) {
			if (!willLog) {
				return *this;
			}

			buffer << a;

			return *this;
		}

		StringBuffer& getBuffer();

		const StringBuffer& getBuffer() const;

		const Logger& getLogger() const;

		bool getWillLog() const;

		int getLogLevel() const;

		bool getBoolParam() const;
	};

	class Logger {
	public:
		static Logger console;

#ifdef PLATFORM_WIN
#undef ERROR
#endif

		enum LogLevel {
			NONE = -1,

			FATAL = 0,
			ERROR = 1,
			WARNING = 2,

			LOG = 3,
			INFO = 4,
			DEBUG = 5
		};

		enum CallbackResult {
			SUCCESS = 0,
			DONTLOG = 1
		};

		using LoggerCallback = Function<int(LogLevel level, const char* message)>;

	private:
		mutable Reference<FileLogWriter*> logFile = nullptr;

		LogLevel logLevel = LOG;
		bool doGlobalLog = true;
		bool doSyncLog = true;
		bool logTimeToFile = true;
		bool logLevelToFile = true;

		String name;

		bool logJSON = false;
		bool logToConsole = true;

		UniqueReference<LoggerCallback*> callback;

		String rotatePrefix = "zArchive/"; // Default to {dir}/zArchive/{filename}
		uint32 rotateLogSizeMB = 0;

		static Reference<FileLogWriter*> globalLogFile;
		static AtomicInteger globalLogLevel;
		static AtomicBoolean syncGlobalLog;
		static AtomicBoolean jsonGlobalLog;
		static Time starttime;

	public:
		Logger(LogLevel level = LOG);
		Logger(const String& s, LogLevel level = LOG);
		Logger(const Logger& logger);

		Logger(Logger&& logger);

		~Logger();

		Logger& operator=(const Logger& logger);
		Logger& operator=(Logger&& logger);

		static void setGlobalFileLogger(const String& file, uint32 rotateSizeMB = 100, bool rotateOnOpen = false);
		static void setGlobalFileLogLevel(LogLevel level);
		static void setGlobalFileLoggerSync(bool val);
		static void setGlobalFileJson(bool val);

		static void closeGlobalFileLogger(bool force = false);

		void setFileLogger(const String& file, bool appendData = false, bool rotateOnOpen = false);

		const String getLogFileName() const;

		void closeFileLogger(bool force = false);

		void info(const char* msg, bool forcedlog) const;

	 	void info(const char* msg) const;

		void info(const String& msg, bool forcedLog = false) const;
		void info(const StringBuffer& msg, bool forcedLog = false) const;

		LoggerHelper info(bool forcedLog = false) const;

		void log(const char *msg, LogLevel type, bool forceSync = false) const;

		void log(const char* msg) const;

		void log(const String& msg) const;
		void log(const StringBuffer& msg) const;

		LoggerHelper log(bool forceSync = false) const;

		void error(const char* msg) const;
		void error(const String& msg) const;
		void error(const StringBuffer& msg) const;

		LoggerHelper error() const;

		[[ noreturn ]] void fatal(const char* msg) const;
		[[ noreturn ]] void fatal(const String& msg) const;
		[[ noreturn ]] void fatal(const StringBuffer& msg) const;

		LoggerHelper fatal(bool assertion) const;

		LoggerHelper fatal() const;

		void fatal(bool assertion, const char* msg) const;

		void fatal(bool assertion, const String& msg) const;

		void fatal(bool assertion, const StringBuffer& msg) const;

		void debug(const char* msg) const;
		void debug(const String& msg) const;
		void debug(const StringBuffer& msg) const;

		LoggerHelper debug() const;

		void warning(const char* msg) const;
		void warning(const String& msg) const;
		void warning(const StringBuffer& msg) const;

		LoggerHelper warning() const;

		bool hasToLog(LogLevel level) const;

		static void getTime(String& time, bool getFull = true);
		static void getTime(StringBuffer& time, bool getFull = true);

		static void getJSONString(StringBuffer& output, const char* logName, const char* msg, LogLevel type);

		static void printTime(bool getFull = true, bool err = false);

		void getLogType(StringBuffer& buffer, LogLevel type) const;
		static const char* getLogType(LogLevel type);

		static uint64 getElapsedTime();

		static String escapeJSON(const String& input);
		static String unescapeJSON(const String& input);

		static String nsToString(uint64 nanos, bool truncate = false);
		static String msToString(uint64 milli);

		// setters
		void setLogging(bool doLog);

		void setLogLevel(LogLevel level);

		void setInfoLogLevel();

		void setDebugLogLevel();

		void setGlobalLogging(bool doLog);

		void setLogToConsole(bool doLog);

		void setSyncFileLogging(bool val);

		void setLogTimeToFile(bool val);

		void setLogLevelToFile(bool val);

		void setLoggingName(const char* s);

		void setLoggingName(const String& s);

		void setLogJSON(bool val);

		void setLogSynchronized(bool synchronized);

		void setRotateLogSizeMB(uint32 maxSizeMB);

		void setRotatePrefix(String prefix);

		void rotateLogFile();

		void setLoggerCallback(LoggerCallback&& funct);

		void setLoggerCallback(const LoggerCallback& funct);

		void clearLoggerCallback();

		// getters
		String& getLoggingName();

		const String& getLoggingName() const;

		FileLogWriter* getFileLogger() const;

		LogLevel getLogLevel() const;

		bool getLogJSON() const;

		LoggerCallback* getLoggerCallback();

		const LoggerCallback* getLoggerCallback() const;

	};

  } // namespace log
} // namespace engine

using namespace engine::log;
