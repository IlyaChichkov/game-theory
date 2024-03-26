cmake_minimum_required(VERSION 3.26)
project(game_theory)

set(CMAKE_CXX_STANDARD 17)

add_executable(game_theory main.cpp src/team.cpp
        src/game_match.cpp
        src/turn_action.cpp
        src/turn_data.cpp
        src/my_team.cpp
        src/bots/bull_team.cpp
)
