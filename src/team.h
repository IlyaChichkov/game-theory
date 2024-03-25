#ifndef GAME_THEORY_TEAM_H
#define GAME_THEORY_TEAM_H

#include <iostream>
#include <vector>
#include "turn_data.h"
#include "turn_action.h"

class Team
{
protected:
    int production;
    std::vector<std::shared_ptr<ITurnAction>> turn_actions;

public:
    void set_turn_actions(std::vector<std::shared_ptr<ITurnAction>> val)
    {
        turn_actions = val;
    }

    virtual ITurnAction make_turn(TurnData match) = 0;

    virtual ~Team() {}
};

#endif //GAME_THEORY_TEAM_H
