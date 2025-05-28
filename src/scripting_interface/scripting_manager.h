#ifndef SCRIPTING_MANAGER_H
#define SCRIPTING_MANAGER_H

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

void scripting_manager_init();
void scripting_manager_shutdown();
lua_State* scripting_manager_get_lua_state(); // Optional for now, but good for future use

#endif // SCRIPTING_MANAGER_H
