/*#include "Script.h"

namespace rsge
{
	template<>
	void Script::RegisterConstant<int>(int value, char* constantname)
	{
		lua_pushinteger(lua_state, value);
		lua_setglobal(lua_state, constantname);
	}

	template<>
	void Script::RegisterConstant<double>(double value, char* constantname)
	{
		lua_pushnumber(lua_state, value);
		lua_setglobal(lua_state, constantname);
	}

	template<>
	void Script::RegisterConstant<char>(char* value, char* constantname)
	{
		lua_pushstring(lua_state, value);
		lua_setglobal(lua_state, constantname);
	}

	template<>
	void Script::RegisterConstant<bool>(bool value, char* constantname)
	{
		lua_pushboolean(lua_state, value);
		lua_setglobal(lua_state, constantname);
	}

	template<>
	void Script::RegisterConstant<lua_cfunction>(lua_CFunction value, char* constantname)
	{
		lua_pushcfunction(lua_state, value);
		lua_setglobal(lua_state, constantname);
	}
}*/