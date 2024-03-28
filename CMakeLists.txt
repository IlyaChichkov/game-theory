cmake_minimum_required(VERSION 3.26)
project(game_theory)
add_library(lua STATIC IMPORTED)

set(CMAKE_CXX_STANDARD 17)

include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/include)
include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/include/LuaBridge)
include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/lib)

add_executable(game_theory main.cpp src/team.cpp
        src/game_match.cpp
        src/turn_action.cpp
        src/turn_data.cpp
        src/utils.cpp
)

target_link_libraries(game_theory ${CMAKE_SOURCE_DIR}/lib/liblua54.so)