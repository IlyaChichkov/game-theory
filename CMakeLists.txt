cmake_minimum_required(VERSION 3.26)
project(game_theory)

set(CMAKE_CXX_STANDARD 17)

add_executable(game_theory main.cpp src/team.h
        src/game_match.h
        src/turn_action.h
        src/my_team.h
        src/turn_data.h
)
