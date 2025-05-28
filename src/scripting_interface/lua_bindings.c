#include "scripting_interface/scripting_manager.h" // Corrected path
#include <stdio.h>  // For printf
#include <stdlib.h> // For exit, if needed for error handling

static lua_State *L = NULL;

void scripting_manager_init() {
    L = luaL_newstate();
    if (L == NULL) {
        fprintf(stderr, "Error: Cannot create Lua state.\n");
        // Depending on the application's design, you might want to exit or return an error code.
        // For now, we'll print an error and continue, but this is not ideal for a real application.
        return; 
    }
    luaL_openlibs(L);

    // Simple C function callable from Lua
    auto lua_c_test_function = [](lua_State *L_func) -> int {
        int n = lua_gettop(L_func); // Number of arguments
        printf("C: lua_c_test_function called with %d arguments\n", n);
        for (int i = 1; i <= n; i++) {
            printf("C: Arg %d: %s\n", i, lua_tostring(L_func, i));
        }
        lua_pushstring(L_func, "Return value from C"); // Push a return value
        return 1; // Number of return values
    };

    // C function for auraflow.core.log
    auto lua_auraflow_core_log = [](lua_State *L_func) -> int {
        const char *message = luaL_checkstring(L_func, 1);
        printf("LUA_CORE_LOG: %s\n", message);
        return 0; // No return values
    };

    // Register lua_c_test_function globally
    lua_pushcfunction(L, lua_c_test_function);
    lua_setglobal(L, "c_test_function");

    // Register lua_auraflow_core_log under auraflow.core.log
    lua_newtable(L); // Create 'auraflow' table
    lua_newtable(L); // Create 'core' table inside 'auraflow'

    lua_pushcfunction(L, lua_auraflow_core_log);
    lua_setfield(L, -2, "log"); // auraflow.core.log = lua_auraflow_core_log

    lua_setfield(L, -2, "core"); // auraflow.core = core_table
    lua_setglobal(L, "auraflow"); // _G.auraflow = auraflow_table
    
    printf("Lua Engine Initialized and C functions registered.\n"); // Modified message

    printf("C: Attempting to load and run 'scripts/main_user_startup.lua'\n");
    if (luaL_dofile(L, "scripts/main_user_startup.lua") != LUA_OK) {
        fprintf(stderr, "C: Error running script: %s\n", lua_tostring(L, -1));
        // lua_pop(L, 1); // Pop error message from stack
    } else {
         printf("C: Successfully executed 'scripts/main_user_startup.lua'\n");
    }
}

void scripting_manager_shutdown() {
    if (L) {
        lua_close(L);
        L = NULL;
    }
    printf("Lua Engine Shutdown.\n");
}

lua_State* scripting_manager_get_lua_state() {
    return L;
}
