#ifndef GAME_THEORY_MY_TEAM_H
#define GAME_THEORY_MY_TEAM_H

#include "turn_data.h"
#include "turn_action.h"
#include "team.h"

class MyTeam : public Team {
public:
    MyTeam(int _id) {
        id = _id;
    }

    void set_prod(int val) {
        production = val;
    }

    ITurnAction make_turn(TurnData match) override {
        std::cout << "[" << id << "] Making turn:" << std::endl;

        auto inc = get_increase_production_actions();
        std::cout << "get_increase_production_actions:" << inc.size() << std::endl;
        auto dec = get_decrease_production_actions();
        std::cout << "get_decrease_production_actions:" << dec.size() << std::endl;
        auto un = get_unchanged_production_actions();
        std::cout << "get_unchanged_production_actions:" << un.size() << std::endl;

        auto str = get_strike_actions();
        std::cout << "get_strike_actions:" << str.size() << std::endl;

        ITurnAction& action = *turn_actions.at(0);

        if (!this->turn_actions.empty()) {
            turn_actions.erase(turn_actions.begin());
        }

        if(action.actionType == TurnActionType::None)
        {
            std::cout << "None" << std::endl;
        }
        if(action.actionType == TurnActionType::ProductionChange)
        {
            std::cout << "ProductionChange" << std::endl;
        }
        if(action.actionType == TurnActionType::Strike)
        {
            std::cout << "Strike" << std::endl;
        }

        return action;
    }

    ~MyTeam() {

    }
};


#endif //GAME_THEORY_MY_TEAM_H
