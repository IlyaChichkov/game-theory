#ifndef GAME_THEORY_MY_TEAM_H
#define GAME_THEORY_MY_TEAM_H

#include <iostream>
#include "team.h"

class MyTeam : public Team {
public:
    explicit MyTeam(int _id);
    int get_rand(int from, int to);
    std::shared_ptr<ITurnAction> make_turn(TurnData match);
    ~MyTeam();
};


#endif //GAME_THEORY_MY_TEAM_H
