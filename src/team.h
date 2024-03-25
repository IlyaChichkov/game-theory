#ifndef GAME_THEORY_TEAM_H
#define GAME_THEORY_TEAM_H

#include <iostream>
#include <vector>
#include "turn_data.h"
#include "turn_action.h"

class Team
{
protected:
    int id;
    int production;
    std::vector<std::shared_ptr<ITurnAction>> turn_actions;

public:
    void set_turn_actions(std::vector<std::shared_ptr<ITurnAction>> val)
    {
        turn_actions = val;
    }

    std::vector<std::shared_ptr<ITurnAction>> get_increase_production_actions() {
        std::vector<std::shared_ptr<ITurnAction>> list;
        for (const auto &a : turn_actions) {
            std::shared_ptr<ProductionChange> action = std::dynamic_pointer_cast<ProductionChange>(a);
            if(action && action->delta > 0) {
                list.push_back(action);
            }
        }
        return list;
    }

    std::vector<std::shared_ptr<ITurnAction>> get_decrease_production_actions() {
        std::vector<std::shared_ptr<ITurnAction>> list;
        for (const auto &a : turn_actions) {
            std::shared_ptr<ProductionChange> action = std::dynamic_pointer_cast<ProductionChange>(a);
            if(action && action->delta < 0) {
                list.push_back(action);
            }
        }
        return list;
    }

    std::vector<std::shared_ptr<ITurnAction>> get_unchanged_production_actions() {
        std::vector<std::shared_ptr<ITurnAction>> list;
        for (const auto &a : turn_actions) {
            std::shared_ptr<ProductionChange> action = std::dynamic_pointer_cast<ProductionChange>(a);
            if(action && action->delta == 0) {
                list.push_back(action);
            }
        }
        return list;
    }

    std::vector<std::shared_ptr<ITurnAction>> get_strike_actions() {
        std::vector<std::shared_ptr<ITurnAction>> list;
        for (const auto &a : turn_actions) {
            std::shared_ptr<ProvokeStrike> action = std::dynamic_pointer_cast<ProvokeStrike>(a);
            if(action) {
                list.push_back(action);
            }
        }
        return list;
    }

    virtual ITurnAction make_turn(TurnData match) = 0;

    virtual ~Team() {}
};

#endif //GAME_THEORY_TEAM_H
