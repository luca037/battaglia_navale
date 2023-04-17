cmake_minimum_required(VERSION 2.84)

set(CMAKE_CXX_STANDARD 11)

set(GCC_COVERGE_COMPILE_FLAGS "-g -O2")

project(ProFinale)

include_directories(include)

add_library(ProFinale
    include/Coordinate.h
    include/Battlefield.h
    include/Submarine.h
    include/BattleShip.h
    include/SupportVessel.h
    include/Human.h
    include/Computer.h
    include/NavalUnit.h
    include/Player.h
    src/Coordinate.cpp
    src/Battlefield.cpp
    src/Submarine.cpp
    src/BattleShip.cpp
    src/SupportVessel.cpp
    src/Human.cpp
    src/Computer.cpp
    )

add_executable(battaglia_navale 
    src/battaglia_navale.cpp
    )

add_executable(replay
    src/replay.cpp
    )

target_link_libraries(battaglia_navale ProFinale)
target_link_libraries(replay ProFinale)
