#include "my_team.h"

MyTeam::MyTeam(int _id) {
    id = _id;
}

void MyTeam::set_prod(int val) {
    production = val;
}

std::shared_ptr<ITurnAction> MyTeam::make_turn(TurnData match) {
    std::cout << "[" << id << "] Making turn:" << std::endl;

    auto inc = get_increase_production_actions();
    std::cout << "get_increase_production_actions:" << inc.size() << std::endl;
    auto dec = get_decrease_production_actions();
    std::cout << "get_decrease_production_actions:" << dec.size() << std::endl;
    auto un = get_unchanged_production_actions();
    std::cout << "get_unchanged_production_actions:" << un.size() << std::endl;

    auto str = get_strike_actions();
    std::cout << "get_strike_actions:" << str.size() << std::endl;

    std::shared_ptr<ITurnAction> action = turn_actions.at(0);

    if (!this->turn_actions.empty()) {
        turn_actions.erase(turn_actions.begin());
    }

    if(action->actionType == TurnActionType::None)
    {
        std::cout << "None" << std::endl;
    }
    if(action->actionType == TurnActionType::ProductionChange)
    {
        std::cout << "ProductionChange" << std::endl;
    }
    if(action->actionType == TurnActionType::Strike)
    {
        std::cout << "Strike" << std::endl;
    }

    return action;
}

MyTeam::~MyTeam() {

}