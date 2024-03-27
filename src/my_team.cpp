#include "my_team.h"

std::shared_ptr<ITurnAction> MyTeam::make_turn(TurnData data) {
    // auto inc = get_increase_production_actions();
    // std::cout << "get_increase_production_actions:" << inc.size() << std::endl;
    // auto dec = get_decrease_production_actions();
    // std::cout << "get_decrease_production_actions:" << dec.size() << std::endl;
    // auto un = get_unchanged_production_actions();
    // std::cout << "get_unchanged_production_actions:" << un.size() << std::endl;
    // auto str = get_strike_actions();
    // std::cout << "get_strike_actions:" << str.size() << std::endl;

    std::shared_ptr<ITurnAction> action = turn_actions.at(Utils::get_rand_int(0, turn_actions.size()));

    switch (action->actionType) {
        case TurnActionType::None:
            std::cerr << "Error: Action type set to None!\n";
            break;
        case TurnActionType::ProductionChange:
            break;
        case TurnActionType::Strike:
            std::shared_ptr<ProvokeStrike> strike = std::dynamic_pointer_cast<ProvokeStrike>(action);
            auto opponents = data.get_opponents(id);
            strike->set_target(opponents.at(Utils::get_rand_int(0, opponents.size())));
            break;
    }

    return action;
}

MyTeam::MyTeam(int _id) : Team(_id) {

}

MyTeam::MyTeam(int _id, std::string _name) : Team(_id, _name) {

}

MyTeam::~MyTeam() = default;