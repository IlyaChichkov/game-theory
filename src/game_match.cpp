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
        int team_id = i;
        auto team = std::make_shared<MyTeam>(team_id);
        team->set_production(initial_production);
        auto actions = matchActions.Create();
        for (const auto action: actions) {
            if(action->actionType == TurnActionType::ProductionChange)
            {
                std::shared_ptr<ProductionChange> pc = std::dynamic_pointer_cast<ProductionChange>(action);
                pc->SetOwner(team_id);
            }
        }
        team->set_turn_actions(actions);
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

GameMatch::~GameMatch() {

}
