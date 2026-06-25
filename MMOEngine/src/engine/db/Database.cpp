#include "Database.h"

void Database::escapeString(String& s) {
	if (s.isEmpty())
		return;

	StringBuffer buf;

	for (int i = 0; i < s.length(); ++i) {
		char ch = s.charAt(i);

		switch (ch) {
			case '\0': // Must be escaped for "mysql"
				buf << "\\0";
				break;
			case '\n': // Must be escaped for logs
				buf << "\\n";
				break;
			case '\r':
				buf << "\\r";
				break;
			case '\\':
				buf << "\\\\";
				break;
			case '\"':
				buf << "\\\"";
				break;
			case '\'': // Better safe than sorry
				buf << "\\\'";
				break;
				/*case '\032': // This gives problems on Win32
				 buf << "\\Z";
				 break;*/
			default:
				buf << ch;
				break;
		}
	}

	s = buf.toString();
}