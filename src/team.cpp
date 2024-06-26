#include "team.h"


Team::Team(int _id) {
    id = _id;
}

Team::Team(int _id, std::string _name, std::string _filePath) {
    id = _id;
    name = _name;
    filePath = _filePath;
}

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

int Team::get_next_production()
{
    return next_production;
}

void Team::set_next_production(int val)
{
    next_production = val;
}

int Team::get_funds() {
    return funds;
}

void Team::pay_production_cost() {
    int cost = (int)(get_production() * 1.8);
    funds_delta_per_turn -= cost;
    funds -= cost;
}

void Team::add_funds(int val) {
    funds_delta_per_turn = val;
    funds += val;
}

void Team::apply_strike() {
    has_strike = true;
}

void Team::before_turn() {
    set_next_production(get_production());
}

void Team::after_turn() {
    if(has_strike) {
        int p = get_next_production() / 2;
        if(p < 100) {
            p = 100;
        }
        set_next_production(p);
        has_strike = false;
    }
    set_production(get_next_production());
}

std::vector<std::shared_ptr<ITurnAction>> Team::get_increase_production_actions() {
    std::vector<std::shared_ptr<ITurnAction>> list;
    for (const auto &a : turn_actions) {
        std::shared_ptr<ProductionChange> action = std::dynamic_pointer_cast<ProductionChange>(a);
        if(action && action->get_delta() > 0) {
            list.push_back(action);
        }
    }
    return list;
}

std::vector<std::shared_ptr<ITurnAction>> Team::get_decrease_production_actions() {
    std::vector<std::shared_ptr<ITurnAction>> list;
    for (const auto &a : turn_actions) {
        std::shared_ptr<ProductionChange> action = std::dynamic_pointer_cast<ProductionChange>(a);
        if(action && action->get_delta() < 0) {
            list.push_back(action);
        }
    }
    return list;
}

std::vector<std::shared_ptr<ITurnAction>> Team::get_unchanged_production_actions() {
    std::vector<std::shared_ptr<ITurnAction>> list;
    for (const auto &a : turn_actions) {
        std::shared_ptr<ProductionChange> action = std::dynamic_pointer_cast<ProductionChange>(a);
        if(action && action->get_delta() == 0) {
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



