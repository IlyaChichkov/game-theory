#include "bull_team.h"

std::shared_ptr<ITurnAction> BullTeam::make_turn(TurnData data) {
    // 1) Использовать карты повышения продукции
    auto increaseActions = get_increase_production_actions();
    if(!increaseActions.empty())
    {
        std::shared_ptr<ITurnAction> action = increaseActions.at(0);

        return action;
    }

    // 2) Использовать карты забастовки
    auto strikeActions = get_strike_actions();
    if(!strikeActions.empty())
    {
        std::shared_ptr<ITurnAction> action = strikeActions.at(0);
        std::shared_ptr<ProvokeStrike> strike = std::dynamic_pointer_cast<ProvokeStrike>(action);
        auto opponents = data.get_opponents(id);

        int strike_id = 0;
        int max_production = 0;

        for (int i = 0; i < opponents.size(); ++i) {
            const auto& opponent = opponents.at(i);
            if(opponent->get_production() > max_production) {
                max_production = opponent->get_production();
                strike_id = i;
            }
        }

        strike->SetTarget(opponents.at(strike_id));
        return action;
    }

    // 3) Использовать оставшиеся карты
    std::shared_ptr<ITurnAction> action = turn_actions.at(0);
    if (!this->turn_actions.empty()) {
        turn_actions.erase(turn_actions.begin());
    }
    return action;
}

BullTeam::BullTeam(int _id) : Team(_id) {

}

BullTeam::BullTeam(int _id, std::string _name) : Team(_id, _name) {

}

BullTeam::~BullTeam() {

}