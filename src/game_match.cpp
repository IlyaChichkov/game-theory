#include "game_match.h"
#include "team.h"
#include "my_team.h"
#include "bots/bull_team.h"
#include "bots/angry_team.h"
#include "turn_action.h"


std::vector<std::shared_ptr<ITurnAction>> DefaultMatchActions::create() const  {
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

    teams.push_back(std::make_shared<BullTeam>(0, "Bull A"));
    teams.push_back(std::make_shared<BullTeam>(1, "Bull B"));
    teams.push_back(std::make_shared<AngryTeam>(2, "Gore C"));
    teams.push_back(std::make_shared<MyTeam>(3, "Randy "));

    for (int i = 0; i < 4; ++i) {
        auto team = teams.at(i);
        int team_id = team->ID();
        team->set_production(initial_production);
        auto actions = matchActions.create();
        for (const auto action: actions) {
            if(action->actionType == TurnActionType::ProductionChange) {
                std::shared_ptr<ProductionChange> pc = std::dynamic_pointer_cast<ProductionChange>(action);
                pc->set_owner(team_id);
            }
        }
        team->set_turn_actions(actions);
    }
}

void GameMatch::complete_turn() {
    TurnData turnData;
    turnData.teams = teams;

    for(const auto& team : this->teams) {
        team->before_turn();
    }

    // Выполнение хода каждой команды
    for(const auto& team : this->teams) {
        std::cout << "Team_" << team->ID() << std::endl;
        auto selectedAction = team->make_turn(turnData);
        selectedAction->complete(&turnData);

        auto& actions = team->turn_actions;
        actions.erase(std::remove(actions.begin(), actions.end(), selectedAction), actions.end());
    }

    for(const auto& team : this->teams) {
        team->after_turn();
    }

    compute_turn_results();

    for(const auto& team : this->teams) {
        team->pay_production_cost();
        team->add_funds(get_income(team->get_production()));
    }
}

void GameMatch::compute_turn_results() {
    total_production = 0;
    for(const auto& team : this->teams) {
        total_production += team->get_production();
    }
    int max_production = 1000;
    sell_price = (int)(70 * max_production / total_production);
}

int GameMatch::get_income(int production) {
    return (int)(production * sell_price);
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
    std::cout << "|----------- TURN RESULTS -----------|" << std::endl;
    for(const auto& team : this->teams) {
        std::cout << "| [" << team->ID() << "] " << team->name << "; Prod: " << team->get_production() << " Funds: " << team->get_funds() << " (+" << team->funds_delta_per_turn << ")" << std::endl;
    }
    std::cout << "|------------------------------------|" << std::endl;
}

void GameMatch::print_match_results() {
    std::cout << "|----------- MATCH RESULTS ----------|" << std::endl;
    int max_production = 0;
    for(const auto& team : this->teams) {
        if(team->get_production() > max_production) {
            max_production = team->get_production();
        }
    }

    std::cout << "| Production Winners:" << std::endl;
    for(const auto& team : this->teams) {
        if(team->get_production() == max_production) {
            std::cout << "| [" << team->ID() << "] " << team->name << std::endl;
        }
    }

    int max_funds = 0;
    for(const auto& team : this->teams) {
        if(team->get_funds() > max_funds) {
            max_funds = team->get_funds();
        }
    }

    std::cout << "| Funds:" << std::endl;
    for(const auto& team : this->teams) {
        if(team->get_funds() == max_funds) {
            std::cout << "| [" << team->ID() << "] " << team->name << " - funds = " << team->get_funds() << " winner!" << std::endl;
        }
        else {
            std::cout << "| [" << team->ID() << "] " << team->name << " - funds = " << team->get_funds() << std::endl;
        }
    }

    std::cout << "|------------------------------------|" << std::endl;
}

GameMatch::~GameMatch() {

}
