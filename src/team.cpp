#include "team.h"


void Team::set_turn_actions(std::vector<std::shared_ptr<ITurnAction>> val)
{
    turn_actions = val;
}

int Team::get_production()
{
    return production;
}

void Team::set_production(int val)
{
    production = val;
}

std::vector<std::shared_ptr<ITurnAction>> Team::get_increase_production_actions() {
    std::vector<std::shared_ptr<ITurnAction>> list;
    for (const auto &a : turn_actions) {
        std::shared_ptr<ProductionChange> action = std::dynamic_pointer_cast<ProductionChange>(a);
        if(action && action->GetDelta() > 0) {
            list.push_back(action);
        }
    }
    return list;
}

std::vector<std::shared_ptr<ITurnAction>> Team::get_decrease_production_actions() {
    std::vector<std::shared_ptr<ITurnAction>> list;
    for (const auto &a : turn_actions) {
        std::shared_ptr<ProductionChange> action = std::dynamic_pointer_cast<ProductionChange>(a);
        if(action && action->GetDelta() < 0) {
            list.push_back(action);
        }
    }
    return list;
}

std::vector<std::shared_ptr<ITurnAction>> Team::get_unchanged_production_actions() {
    std::vector<std::shared_ptr<ITurnAction>> list;
    for (const auto &a : turn_actions) {
        std::shared_ptr<ProductionChange> action = std::dynamic_pointer_cast<ProductionChange>(a);
        if(action && action->GetDelta() == 0) {
            list.push_back(action);
        }
    }
    return list;
}

std::vector<std::shared_ptr<ITurnAction>> Team::get_strike_actions() {
    std::vector<std::shared_ptr<ITurnAction>> list;
    for (const auto &a : turn_actions) {
        std::shared_ptr<ProvokeStrike> action = std::dynamic_pointer_cast<ProvokeStrike>(a);
        if(action) {
            list.push_back(action);
        }
    }
    return list;
}

int Team::ID() const {
    return id;
}

Team::~Team() {}
