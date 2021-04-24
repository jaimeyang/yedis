cmake_minimum_required(VERSION 3.12)
project(yedis)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_definitions("-Wall -g")
add_definitions(-DUSE_STATIC_LIB)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

set(CMAKE_CXX_STANDARD 17)
set(IS_TEST "ON")

include_directories(core)
include_directories(core/base)
include_directories(common)
include_directories(thread)
include_directories(db/cache)
include_directories(db/mysql)
include_directories(net)
include_directories(lua/LuaBridge/Source/)
include_directories(lua/)
include_directories(lib/lua/include/)
include_directories(lib/zookeeper-client-c/include)
include_directories(worker)
# spdlog
include_directories(lib/spdlog/include)
# mysql
include_directories(lib/mysql/include)
include_directories(lib/mysql/client/include)
# kafka
include_directories(lib/kafka/include)

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

# set(LUA_SRC )


set(SOURCE_FILES ${DIR_JSON_SRCS}
        mempool/lua/MemPool.cpp
        mempool/lua/MemPool.h
        common/CpuInfo.h
        common/Param.h
        thread/IThread.cpp
        net/INetEvent.cpp
        net/INetEvent.h
        net/IStream.cpp
        net/IStream.h
        common/Msg.h
        net/NetProxy.cpp
        net/NetProxy.h
        net/StreamConnect.cpp
        net/StreamConnect.h
        net/StreamListen.cpp
        net/StreamListen.h
        net/StreamBuf.cpp
        net/StreamBuf.h
        worker/Worker.cpp
        worker/Worker.h
        worker/Wmanager.cpp
        worker/Wmanager.h 
        lua/LuaFactory.cpp
        net/Params.h)
#        main.cpp)


set(MYSQL 
            db/mysql/Mysql.cpp
            db/mysql/MySqlclient.cpp)

set(Redis
            db/cache/Redis.cpp)

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux" )
    OPTION(DEFINE_LINUX"Option System" ON)
    ADD_DEFINITIONS(-DLINUX)

    set(HOST_SYSTEM_SRC thread/LinuxPth.cpp
            net/LinuxNevent.cpp
            net/LinuxNevent.h
            net/LinuxStream.cpp
            net/LinuxStream.h
            net/LinuxConnect.cpp
            net/LinuxConnect.h
            net/LinuxListen.cpp
            net/LinuxListen.h)
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(HOST_SYSTEM_SRC thread/WinPth.cpp)
endif()

include (CheckIncludeFile)
check_include_file("sys/epoll.h" HAVE_EPOLL_H)
if (HAVE_EPOLL_H)
    OPTION(DEFINE_EPOLL"Option description" ON)
    ADD_DEFINITIONS(-DEPOLL)
    set(MULTI_SRC
            net/Epoll.cpp
            net/Epoll.h)
endif (HAVE_EPOLL_H)

#gtest unit src
set(TEST_SRC 
            test/luacrossc/TestLuaCrossC.cpp
            test/luacrossc/TestLuaCModule.cpp
            test/cpu/TestCpu.cpp
            test/mempool/TestMemPool.cpp
            test/mempool/TestMemPool.h
            test/zookeeper/TestZookeeper.cpp
            test/phtread/linux/TestPthread.cpp
            test/net/TestNet.cpp
            test/net/TestNet.h
            test/luafactory/TestLuaFactory.cpp
            test/mysql/TestMysql.cpp
            test/mysql/TestMyClient.cpp
            test/kafka/TestKafka.cpp
            test/redis/TestRedis.cpp
            )

# zookeeper
link_directories(lib/zookeeper-client-c/lib)
# spdlog
link_directories(lib/spdlog/lib)
# mysql
link_directories(lib/mysql/lib64)
link_directories(lib/mysql/client/lib)
# kafka
link_directories(lib/kafka/lib)

if (${IS_TEST} STREQUAL "ON")
    #benchmark
    include_directories(lib/benchmark/include)
    link_directories(lib/benchmark)
    # gtest
    include_directories(lib/googletest/googletest/include)
    link_directories(lib/googletest/lib)
else()
endif()


add_executable(yedis ${MULTI_SRC}
        ${SOURCE_FILES}
        ${LUA_LIB_SRC}
        ${HOST_SYSTEM_SRC}
        ${MYSQL}
        ${REDIS})

if (${IS_TEST} STREQUAL "ON")
    
    target_link_libraries(yedis benchmark benchmark_main)
    target_link_libraries(yedis gtest gtest_main)

    target_sources(yedis PRIVATE ${TEST_SRC})
    target_sources(yedis PRIVATE gtestmain.cpp)

else()
    target_sources(yedis PRIVATE main.cpp)
endif ()


target_link_libraries(yedis rdkafka++)
target_link_libraries(yedis zookeeper)
target_link_libraries(yedis hashtable)
target_link_libraries(yedis ssl)
target_link_libraries(yedis crypto)
target_link_libraries(yedis hiredis)
target_link_libraries(yedis pthread)
target_link_libraries(yedis m)
target_link_libraries(yedis spdlog)
target_link_libraries(yedis mysqlcppconn8)
target_link_libraries(yedis mysqlclient)


