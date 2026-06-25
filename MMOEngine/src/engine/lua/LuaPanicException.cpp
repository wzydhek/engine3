#include "system/lang/Exception.h"
#include "LuaPanicException.h"

LuaPanicException::LuaPanicException(const String& msg) : Exception(msg) {
}