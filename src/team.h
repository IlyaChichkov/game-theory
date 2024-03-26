#ifndef GAME_THEORY_TEAM_H
#define GAME_THEORY_TEAM_H

#include <iostream>
#include <vector>
#include "turn_action.h"
#include "turn_data.h"

class ITurnAction;

class Team
{
protected:
    int id;
    int production;

public:
    std::vector<std::shared_ptr<ITurnAction>> turn_actions;

    Team(int _id);
    void set_turn_actions(std::vector<std::shared_ptr<ITurnAction>> val);
    int get_production();
    void set_production(int val);

    std::vector<std::shared_ptr<ITurnAction>> get_increase_production_actions();
    std::vector<std::shared_ptr<ITurnAction>> get_decrease_production_actions();
    std::vector<std::shared_ptr<ITurnAction>> get_unchanged_production_actions();
    std::vector<std::shared_ptr<ITurnAction>> get_strike_actions();

    int ID() const;

    virtual std::shared_ptr<ITurnAction> make_turn(TurnData match) = 0;
    virtual ~Team();
};

#endif //GAME_THEORY_TEAM_H
