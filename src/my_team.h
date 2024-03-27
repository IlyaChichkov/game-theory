#ifndef GAME_THEORY_MY_TEAM_H
#define GAME_THEORY_MY_TEAM_H

#include <iostream>
#include "utils.h"
#include "team.h"

class MyTeam : public Team {
public:
    explicit MyTeam(int _id);
    explicit MyTeam(int _id, std::string _name);
    std::shared_ptr<ITurnAction> make_turn(TurnData match) override;
    ~MyTeam();
};


#endif //GAME_THEORY_MY_TEAM_H
