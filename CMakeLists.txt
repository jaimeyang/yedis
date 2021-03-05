cmake_minimum_required(VERSION 3.12)
project(yedis)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_definitions("-Wall -g")
set(CMAKE_CXX_STANDARD 17)
set(IS_TEST "ON")

include_directories(core)
include_directories(core/base)
include_directories(db/cache)
include_directories(lib/lua/include/)

#add build lua
set(LUA_LIB_SRC lib/lua/src/lapi.c
        lib/lua/src/lauxlib.c
        lib/lua/src/lbaselib.c
        lib/lua/src/lcode.c
        lib/lua/src/lcorolib.c
        lib/lua/src/lctype.c
        lib/lua/src/ldblib.c
        lib/lua/src/ldebug.c
        lib/lua/src/ldo.c
        lib/lua/src/ldump.c
        lib/lua/src/lfunc.c
        lib/lua/src/lgc.c
        lib/lua/src/linit.c
        lib/lua/src/liolib.c
        lib/lua/src/llex.c
        lib/lua/src/lmathlib.c
        lib/lua/src/lmem.c
        lib/lua/src/loadlib.c
        lib/lua/src/lobject.c
        lib/lua/src/lopcodes.c
        lib/lua/src/loslib.c
        lib/lua/src/lparser.c
        lib/lua/src/lstate.c
        lib/lua/src/lstring.c
        lib/lua/src/lstrlib.c
        lib/lua/src/ltable.c
        lib/lua/src/ltablib.c
        lib/lua/src/ltm.c
        lib/lua/src/lundump.c
        lib/lua/src/lutf8lib.c
        lib/lua/src/lvm.c
        lib/lua/src/lzio.c)

set(LUA_SRC  lua/LuaScript.cpp
        lua/LuaScript.h lua/LuaCommon.h)


set(SOURCE_FILES ${DIR_JSON_SRCS}
        core/Object.cpp
        core/EventFactory.cpp
        core/Event.cpp
        core/Server.cpp
        core/ServerObj.cpp
        core/EpollDispatcher.cpp
        core/Worker.cpp
        core/Worker.h
        db/cache/Redis.cpp
        db/cache/Redis.h
        core/pool/WorkerPool.cpp
        core/pool/WorkerPool.h
        core/WorkerObject.cpp
        core/WorkerObject.h
        core/base/Interger.cpp
        core/base/Interger.h
        core/TcpEventObj.h
        core/Buffer.cpp
        core/Buffer.h core/pool/MemPool.cpp core/pool/MemPool.h)
#        main.cpp)
#gtest unit src
set(TEST_SRC test/luacrossc/TestLuaCrossC.cpp)

add_executable(yedis ${SOURCE_FILES}
        ${LUA_LIB_SRC}
        ${LUA_SRC})

if (${IS_TEST} STREQUAL "ON")
    target_sources(yedis PRIVATE ${TEST_SRC})
    include_directories(lib/googletest/googletest/include)
    #gtest
    add_subdirectory(lib/googletest)
    #gtest
    target_link_libraries(yedis gtest gtest_main)
else()
    target_sources(yedis PRIVATE main.cpp)
endif ()

target_link_libraries(yedis hiredis)
target_link_libraries(yedis pthread)
target_link_libraries(yedis m)


