#include "turn_action.h"

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
    std::cout << "Complete ProductionChange" << std::endl;
}

ProvokeStrike::ProvokeStrike() {
    actionType = TurnActionType::Strike;
    strikeTarget = nullptr;
}

void ProvokeStrike::Complete(TurnData *turnData) const {
    //for (auto team_ptr : turnData->teams) {
        // team_ptr->ID();
    //}
    std::cout << "Complete ProvokeStrike" << std::endl;
}

void ProvokeStrike::SetTarget(Team *target) {
    strikeTarget = target;
}
