cmake_minimum_required(VERSION 3.12)
project(robot)

add_definitions("-Wall -g")


set(SOURCE_FILES ${DIR_JSON_SRCS}
        core/Object.cpp
        core/EventFactory.cpp
        core/Event.cpp
        core/Server.cpp
        core/EpollDispatcher.cpp
        main.cpp)

add_executable(robot ${SOURCE_FILES})


