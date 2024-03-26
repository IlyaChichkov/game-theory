#include "game_match.h"
#include "team.h"
#include "my_team.h"
#include "turn_action.h"


std::vector<std::shared_ptr<ITurnAction>> DefaultMatchActions::Create() const  {
    std::vector<std::shared_ptr<ITurnAction>> actions;
    actions.push_back(std::make_shared<ProductionChange>(-10));
    actions.push_back(std::make_shared<ProductionChange>(-10));
    actions.push_back(std::make_shared<ProductionChange>(-20));
    actions.push_back(std::make_shared<ProductionChange>(-20));
    actions.push_back(std::make_shared<ProductionChange>(10));
    actions.push_back(std::make_shared<ProductionChange>(10));
    actions.push_back(std::make_shared<ProductionChange>(20));
    actions.push_back(std::make_shared<ProductionChange>(20));
    actions.push_back(std::make_shared<ProductionChange>(30));
    actions.push_back(std::make_shared<ProductionChange>(30));
    actions.push_back(std::make_shared<ProductionChange>(50));
    actions.push_back(std::make_shared<ProductionChange>(0));
    actions.push_back(std::make_shared<ProvokeStrike>());
    actions.push_back(std::make_shared<ProvokeStrike>());
    return actions;
}

void GameMatch::setup_teams() {
    int initial_production = 250;
    DefaultMatchActions matchActions;

    for (int i = 0; i < 4; ++i) {
        MyTeam* team = new MyTeam(i);
        team->set_prod(initial_production);
        team->set_turn_actions(matchActions.Create());
        teams.push_back(team);
    }
}

void GameMatch::complete_turn() {
    TurnData turnData;
    turnData.teams = teams;

    for(const auto& team : this->teams)
    {
        auto selectedAction = team->make_turn(turnData);
        selectedAction->Complete(&turnData);
    }

    compute_turn_results();
}

void GameMatch::compute_turn_results() {

}

void GameMatch::start() {
    setup_teams();
    for (int i = 0; i < 14; ++i) {
        complete_turn();
    }
}

void GameMatch::add_strike(Team *strikeTeam) {
    this->strikeTeams.push_back(strikeTeam);
}

GameMatch::~GameMatch() {
    for (auto* team : teams) {
        delete team;
    }

    for (auto* team : strikeTeams) {
        delete team;
    }
}
