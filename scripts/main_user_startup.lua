-- AuraFlow User Startup Script Example
-- This script can be configured to run when AuraFlow starts.

print("AuraFlow Lua: main_user_startup.lua loaded!")

-- Hypothetical API usage:
if auraflow and auraflow.core then
    auraflow.core.log_message("INFO", "Hello from 'main_user_startup.lua' script!")

    -- Example: Register a simple command
    -- auraflow.commands.register("my_lua_cmd", function(args)
    --   auraflow.core.log_message("INFO", "my_lua_cmd executed with args: " .. table.concat(args or {}, ", "))
    --   return "Command successful!"
    -- end)

    -- Example: Subscribe to an application event
    -- auraflow.events.subscribe("core.project_loaded", function(event_data)
    --    auraflow.core.log_message("INFO", "Lua detected project loaded: " .. event_data.project_name)
    -- end)
else
    print("AuraFlow Lua: 'auraflow' API object not found. (This is normal if API isn't fully initialized yet or script runs too early)")
end
