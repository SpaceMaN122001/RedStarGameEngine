#ifndef _SCRIPT_H_
#define _SCRIPT_H_

namespace rsge
{
	class Script
	{
	public:
		void create()
		{
			luaState = luaL_newstate();

			static const luaL_Reg lualibs[] =
			{
				{"base", luaopen_base},
				{"io", luaopen_io},
				{NULL, NULL}
			};

			for (const luaL_Reg *lib = lualibs; lib->func != NULL; lib++)
			{
				luaL_requiref(luaState, lib->name, lib->func, 1);
				lua_settop(luaState, 0);
			}
		}
		
		void close()
		{
			lua_close(luaState);
		}

		int doFile(char* pathToScript)
		{
			luaL_dofile(luaState, pathToScript);

			return lua_tointeger(luaState, lua_gettop(luaState));
		}

	private:
		lua_State* luaState;

	protected:
	};
}

#endif