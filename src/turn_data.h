//
// Created by IlyaChichkov on 25.03.2024.
//

#ifndef GAME_THEORY_TURN_DATA_H
#define GAME_THEORY_TURN_DATA_H

#include <iostream>
#include <vector>
#include <memory>

class Team;

class TurnData {
    /*
     *  Содержит всю информацию об игре, командах на
     *  текущем ходе игры
     */
public:
    std::vector<std::shared_ptr<Team>> teams;

    std::vector<std::shared_ptr<Team>> get_opponents(int team_id);
};


#endif //GAME_THEORY_TURN_DATA_H
