#include "game_match.h"
#include "team.h"
#include "my_team.h"
#include "bots/bull_team.h"
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

    teams.push_back(std::make_shared<BullTeam>(0));
    teams.push_back(std::make_shared<BullTeam>(1));
    teams.push_back(std::make_shared<BullTeam>(2));
    teams.push_back(std::make_shared<MyTeam>(3));

    for (int i = 0; i < 4; ++i) {
        auto team = teams.at(i);
        int team_id = team->ID();
        team->set_production(initial_production);
        auto actions = matchActions.Create();
        for (const auto action: actions) {
            if(action->actionType == TurnActionType::ProductionChange) {
                std::shared_ptr<ProductionChange> pc = std::dynamic_pointer_cast<ProductionChange>(action);
                pc->SetOwner(team_id);
            }
        }
        team->set_turn_actions(actions);
    }
}

void GameMatch::complete_turn() {
    TurnData turnData;
    turnData.teams = teams;

    for(const auto& team : this->teams) {
        std::cout << "Team_" << team->ID() << std::endl;
        auto selectedAction = team->make_turn(turnData);
        selectedAction->Complete(&turnData);

        auto& actions = team->turn_actions;
        actions.erase(std::remove(actions.begin(), actions.end(), selectedAction), actions.end());
    }

    compute_turn_results();
}

void GameMatch::compute_turn_results() {

}

void GameMatch::start() {
    setup_teams();
    for (int i = 0; i < 14; ++i) {
        std::cout << "[TURN " << i << "]" << std::endl;
        complete_turn();
        print_turn_results();
    }
    print_match_results();
}

void GameMatch::print_turn_results() {
    std::cout << "> TURN RESULTS <" << std::endl;
    for(const auto& team : this->teams) {
        std::cout << "> Team_" << team->ID() << "; Production: " << team->get_production() << std::endl;
    }
}

void GameMatch::print_match_results() {
    std::cout << "> MATCH RESULTS <" << std::endl;
    int max_production = 0;
    for(const auto& team : this->teams) {
        if(team->get_production() > max_production) {
            max_production = team->get_production();
        }
    }

    std::cout << "Production Winners:" << std::endl;
    for(const auto& team : this->teams) {
        if(team->get_production() == max_production) {
            std::cout << "> Team_" << team->ID() << std::endl;
        }
    }

    int max_funds = 0;
    // TODO: Funds winners compute...
}

GameMatch::~GameMatch() {

}