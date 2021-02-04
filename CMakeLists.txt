cmake_minimum_required(VERSION 3.12)
project(yedis)

add_definitions("-Wall -g")
set(CMAKE_CXX_STANDARD 17)

include_directories(core)
include_directories(core/base)
include_directories(db/cache)


set(SOURCE_FILES ${DIR_JSON_SRCS}
        core/Object.cpp
        core/EventFactory.cpp
        core/Event.cpp
        core/Server.cpp
        core/ServerObj.cpp
        core/EpollDispatcher.cpp
        main.cpp core/Worker.cpp
        core/Worker.h
        db/cache/Redis.cpp
        db/cache/Redis.h
        core/pool/WorkerPool.cpp
        core/pool/WorkerPool.h
        core/WorkerObject.cpp
        core/WorkerObject.h
        core/base/Interger.cpp
        core/base/Interger.h
        core/TcpEventObj.h)

add_executable(yedis ${SOURCE_FILES})

target_link_libraries(yedis hiredis)
target_link_libraries(yedis pthread)

