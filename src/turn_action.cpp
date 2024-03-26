#include "turn_action.h"
#include "team.h"

ProductionChange::ProductionChange(int _delta) {
    actionType = TurnActionType::ProductionChange;
    delta = _delta;
}

void ProductionChange::SetOwner(int _owner_id) {
    owner_id = _owner_id;
}

int ProductionChange::GetDelta()  {
    return delta;
}

void ProductionChange::Complete(TurnData *turnData) const {
    std::cout << "Complete: Production Change | Delta = " << delta << std::endl;
    for (auto team_ptr : turnData->teams) {
        if(team_ptr->ID() == owner_id) {
            team_ptr->set_next_production(team_ptr->get_next_production() + delta);
            break;
        }
    }
}

ProvokeStrike::ProvokeStrike() {
    actionType = TurnActionType::Strike;
    strikeTarget = nullptr;
}

void ProvokeStrike::Complete(TurnData *turnData) const {
    std::cout << "Complete: Provoke Strike | Target is team_" << strikeTarget->ID() << std::endl;
    for (auto team_ptr : turnData->teams) {
        if(team_ptr->ID() == strikeTarget->ID()) {
            team_ptr->apply_strike();
            break;
        }
    }
}

void ProvokeStrike::SetTarget(std::shared_ptr<Team> target) {
    strikeTarget = target;
}
