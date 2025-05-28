print("LUA: main_user_startup.lua loaded!")

-- Test calling a C function registered globally
print("LUA: Calling global c_test_function...")
local result = c_test_function("hello from Lua", "second arg")
print("LUA: Result from c_test_function: " .. (result or "nil"))

-- Test calling a C function registered under a table
if auraflow and auraflow.core and auraflow.core.log then
    print("LUA: Calling auraflow.core.log...")
    auraflow.core.log("This is a test message from Lua via auraflow.core.log!")
else
    print("LUA: auraflow.core.log not found!")
end

print("LUA: End of main_user_startup.lua")
