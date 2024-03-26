#include "my_team.h"

MyTeam::MyTeam(int _id) {
    id = _id;
}

void MyTeam::set_prod(int val) {
    production = val;
}

std::shared_ptr<ITurnAction> MyTeam::make_turn(TurnData data) {
    std::cout << "[TEAM_" << id << "] Making turn:" << std::endl;

    // auto inc = get_increase_production_actions();
    // std::cout << "get_increase_production_actions:" << inc.size() << std::endl;
    // auto dec = get_decrease_production_actions();
    // std::cout << "get_decrease_production_actions:" << dec.size() << std::endl;
    // auto un = get_unchanged_production_actions();
    // std::cout << "get_unchanged_production_actions:" << un.size() << std::endl;
    // auto str = get_strike_actions();
    // std::cout << "get_strike_actions:" << str.size() << std::endl;

    std::shared_ptr<ITurnAction> action = turn_actions.at(0);

    if (!this->turn_actions.empty()) {
        turn_actions.erase(turn_actions.begin());
    }

    switch (action->actionType) {
        case TurnActionType::None:
            std::cerr << "Error: Action type set to None!\n";
            break;
        case TurnActionType::ProductionChange:
            break;
        case TurnActionType::Strike:
            std::shared_ptr<ProvokeStrike> strike = std::dynamic_pointer_cast<ProvokeStrike>(action);
            auto opponents = data.get_opponents(id);
            strike->SetTarget(opponents.at(0));
            break;
    }

    return action;
}

MyTeam::~MyTeam() {

}