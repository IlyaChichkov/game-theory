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
        std::cout << "Making turn..." << std::endl;

        ITurnAction& action = *turn_actions.at(0);

        if (!this->turn_actions.empty()) {
            turn_actions.erase(turn_actions.begin());
        }

        if(action.actionType == TurnActionType::None)
        {
            std::cout << "Error: " << std::endl;
        }
        if(action.actionType == TurnActionType::ProductionChange)
        {
            std::cout << "ProductionChange: " << std::endl;
        }
        if(action.actionType == TurnActionType::Strike)
        {
            std::cout << "Strike: " << std::endl;
        }

        return action;
    }

    ~MyTeam() {

    }
};


#endif //GAME_THEORY_MY_TEAM_H
