#ifndef GAME_THEORY_MY_TEAM_H
#define GAME_THEORY_MY_TEAM_H

#include "turn_data.h"
#include "turn_action.h"
#include "team.h"

class MyTeam : public Team {
public:
    ITurnAction make_turn(TurnData match) const override {
        std::cout << "Making turn..." << std::endl;

        ITurnAction& action = *turn_actions.at(0);

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
        for (ITurnAction* action : turn_actions) {
            delete action;
        }
    }
};


#endif //GAME_THEORY_MY_TEAM_H
