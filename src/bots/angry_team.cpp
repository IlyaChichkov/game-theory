#include "angry_team.h"

std::shared_ptr<ITurnAction> AngryTeam::make_turn(TurnData data) {
    // 1) Использовать карты забастовки
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

    // 2) Использовать карты повышения продукции
    auto increaseActions = get_increase_production_actions();
    if(!increaseActions.empty())
    {
        int max_increase = 0;
        int action_index = 0;
        for (int i = 0; i < increaseActions.size(); ++i) {
            const auto &a = increaseActions.at(i);
            std::shared_ptr<ProductionChange> pc = std::dynamic_pointer_cast<ProductionChange>(a);
            if(pc->GetDelta() > max_increase) {
                max_increase = pc->GetDelta();
                action_index = i;
            }
        }
        std::shared_ptr<ITurnAction> action = increaseActions.at(action_index);

        return action;
    }

    // 3) Использовать оставшиеся карты
    std::shared_ptr<ITurnAction> action = turn_actions.at(0);
    if (!this->turn_actions.empty()) {
        turn_actions.erase(turn_actions.begin());
    }
    return action;
}

AngryTeam::AngryTeam(int _id) : Team(_id) {

}

AngryTeam::AngryTeam(int _id, std::string _name) : Team(_id, _name) {

}

AngryTeam::~AngryTeam() {

}