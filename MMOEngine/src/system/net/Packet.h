/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/platform.h"

#ifndef PLATFORM_WIN
	#include <arpa/inet.h>
#else
	#include <winsock2.h>
#endif

#define HTONLL(x) ((1==htonl(1)) ? (x) : (((uint64_t)htonl((x) & 0xFFFFFFFFUL)) << 32) | htonl((uint32_t)((x) >> 32)))
#define NTOHLL(x) ((1==ntohl(1)) ? (x) : (((uint64_t)ntohl((x) & 0xFFFFFFFFUL)) << 32) | ntohl((uint32_t)((x) >> 32)))

#include "system/lang/String.h"
#include "system/lang/UnicodeString.h"
#include "system/lang/Object.h"
#include "system/io/ObjectInputStream.h"
#include "system/io/ObjectOutputStream.h"
#include "PacketIndexOutOfBoundsException.h"

namespace sys {
  namespace net {

	using namespace sys::lang;

	class Packet : public ObjectInputStream, public ObjectOutputStream {
	public:
		static const int RAW_MAX_SIZE = 496;
		static const uint32 MAX_UNICODE_LENGTH = 33554432U;

	public:
		Packet();
		Packet(int size);

		virtual ~Packet();

		Packet* clone(int startoffs = 0);

		// inserting methods
		void insertBoolean(bool val);

		void insertByte(uint8 val);

		void insertByte(int offs, uint8 val);

		void insertSignedByte(int8 val);

		void insertShort(uint16 val);

		void insertSignedShort(int16 val);

		void insertShort(int offs, uint16 val);

		void insertShortNet(uint16 val);

		void insertInt(uint32 val);

		void insertInt(int offs, uint32 val);

		void insertSignedInt(int32 val);

		void insertIntNet(uint32 val);

		void insertLong(uint64 val);

		void insertLong(int offs, uint64 val);

		void insertSignedLong(int64 val);

		void insertFloat(float val);

		void insertDouble(double val);

		void insertAscii(const char* ascii);

		void insertAscii(const char* ascii, int len);

		void insertAscii(const String& ascii);

		void insertUnicode(const UnicodeString& str);

		void insertStream(const char* buf, int len);

		void insertStream(Stream* stream);

		void insertStream(Stream* stream, int len);

		void insertCString(const char* buf, bool nullTerminator = false);

		// parsing methods
		bool parseBoolean();

		uint8 parseByte();

		uint8 parseByte(int offs);

		int8 parseSignedByte();

		int8 parseSignedByte(int offs);

		uint16 parseShort();

		int16 parseSignedShort();

		int16 parseSignedShort(int offs);

		uint16 parseShort(int offs);

		uint16 parseNetShort();

		uint16 parseNetShort(int offs);

		uint32 parseInt();

		uint32 parseInt(int offs);

		int32 parseSignedInt();

		int32 parseSignedInt(int offs);

		uint32 parseNetInt();

		uint32 parseNetInt(int offs);

		uint64 parseNetLong();

		uint64 parseNetLong(int offs);

		uint64 parseLong();

		uint64 parseLong(int offs);

		int64 parseSignedLong();

		int64 parseSignedLong(int offs);

		float parseFloat();

		double parseDouble();

		float parseFloat(int offs);

		int parseAscii(char* ascii);

		void parseAscii(String& ascii);

		String parseAscii();

		void parseAscii(int offs, String& ascii);

		void parseUnicode(UnicodeString& str);

		UnicodeString parseUnicode();

		void parseUnicode(int offs, UnicodeString& str);

		void parseStream(char* buf, int len);

		void parseStream(Stream* stream, int len);

	};

  } // namespace net
} // namespace sys

using namespace sys::net;
