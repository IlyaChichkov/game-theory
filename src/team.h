#ifndef GAME_THEORY_TEAM_H
#define GAME_THEORY_TEAM_H

#include <iostream>
#include <string>
#include <vector>
#include "turn_action.h"
#include "turn_data.h"

class ITurnAction;

class Team
{
    /*
     *  Абстрактный класс для команды, выполняющей ходы
     */
protected:
    int id;
    int production = 0;
    int next_production = 0;
    int funds = 0;
    bool has_strike = false;

public:
    int funds_delta_per_turn = 0;
    std::string name = "Name";
    std::vector<std::shared_ptr<ITurnAction>> turn_actions;

    Team(int _id);
    Team(int _id, std::string _name);
    void set_turn_actions(std::vector<std::shared_ptr<ITurnAction>> val);

    int get_production();
    void set_production(int val);

    int get_next_production();
    void set_next_production(int val);

    int get_funds();
    void add_funds(int val);
    void apply_strike();

    void before_turn();
    void after_turn();

    std::vector<std::shared_ptr<ITurnAction>> get_increase_production_actions();
    std::vector<std::shared_ptr<ITurnAction>> get_decrease_production_actions();
    std::vector<std::shared_ptr<ITurnAction>> get_unchanged_production_actions();
    std::vector<std::shared_ptr<ITurnAction>> get_strike_actions();

    int ID() const;

    virtual std::shared_ptr<ITurnAction> make_turn(TurnData match) = 0;
    virtual ~Team();
};

#endif //GAME_THEORY_TEAM_H
