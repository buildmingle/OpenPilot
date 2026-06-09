cmake_minimum_required(VERSION 3.10)

project(OpenPilot)

set(CMAKE_CXX_STANDARD 17)

find_package(Lua 5.4 QUIET)

# Prefer Homebrew Lua on macOS, otherwise use system/apt Lua.
if(APPLE)
    set(LUA_INCLUDE_DIR /opt/homebrew/opt/lua@5.4/include)
    set(LUA_LIBRARIES   /opt/homebrew/opt/lua@5.4/lib/liblua.dylib)
endif()

if(NOT LUA_INCLUDE_DIR)
    find_path(LUA_INCLUDE_DIR lua.h HINTS /usr/include /usr/include/lua5.4 /usr/include/lua5.3 /usr/local/include /opt/homebrew/include)
endif()

if(NOT LUA_LIBRARIES)
    find_library(LUA_LIBRARIES NAMES lua5.4 lua lua5.3 HINTS /usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib /opt/homebrew/lib)
endif()

if(NOT LUA_INCLUDE_DIR OR NOT LUA_LIBRARIES)
    message(FATAL_ERROR "Lua headers or libraries not found. Install liblua5.4-dev (or equivalent) and rerun CMake.")
endif()

add_executable(OpenPilot
    src/main.cpp
    src/core.cpp
    src/system.cpp
    src/control.cpp
    src/sensors.cpp
    src/telemetry.cpp
    src/navigation.cpp
    src/car_electric/ignition.cpp
    src/ci_electric/power.cpp
    src/lua_engine.cpp
)

target_include_directories(OpenPilot PRIVATE ./include ${LUA_INCLUDE_DIR})
target_link_libraries(OpenPilot PRIVATE ${LUA_LIBRARIES})
