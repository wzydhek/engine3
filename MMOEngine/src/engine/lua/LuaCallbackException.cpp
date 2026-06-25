#include "LuaCallbackException.h"

LuaCallbackException::LuaCallbackException(lua_State* L, const String& msg) : Exception() {
	luaL_where(L, 1);
	String luaMethodName = lua_tostring(L, -1);

	message = msg + " at " + luaMethodName;
}