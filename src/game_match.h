#ifndef GAME_THEORY_GAME_MATCH_H
#define GAME_THEORY_GAME_MATCH_H

#include <vector>
#include <memory>
#include "team.h"
#include "my_team.h"
#include "turn_action.h"

class MatchActionsFactory {
public:
    virtual std::vector<std::shared_ptr<ITurnAction>> Create() const = 0;
    virtual ~MatchActionsFactory() {} // Virtual destructor for polymorphism
};

class DefaultMatchActions : public MatchActionsFactory {
public:
    [[nodiscard]] std::vector<std::shared_ptr<ITurnAction>> Create() const override {
        std::vector<std::shared_ptr<ITurnAction>> actions;
        actions.push_back(std::make_shared<ProductionChange>(-10));
        actions.push_back(std::make_shared<ProductionChange>(-10));
        actions.push_back(std::make_shared<ProductionChange>(10));
        actions.push_back(std::make_shared<ProductionChange>(10));
        actions.push_back(std::make_shared<ProvokeStrike>());
        return actions;
    }
};

class GameMatch {
    /*
     *  Игровой матч состоящий из 14 ходов
     *  Содержит всю информацию о текущей игре, командах
     */
private:
    std::vector<Team*> teams;
    std::vector<Team*> strikeTeams;

    void setup_teams() {
        int initial_production = 250;
        DefaultMatchActions matchActions;

        for (int i = 0; i < 4; ++i) {
            MyTeam* team = new MyTeam();
            team->set_prod(initial_production);
            team->set_turn_actions(matchActions.Create());
            teams.push_back(team);
        }
    }

    void complete_turn() {
        TurnData turnData;

        for(const auto& team : this->teams)
        {
            ITurnAction selectedAction = team->make_turn(turnData);
        }

        compute_turn_results();
    }

    void compute_turn_results() {

    }

public:

    void start() {
        setup_teams();
        for (int i = 0; i < 5; ++i) {
            complete_turn();
        }
    }

    void add_strike(Team *strikeTeam) {
        this->strikeTeams.push_back(strikeTeam);
    }

    ~GameMatch() {
        for (auto* team : teams) {
            delete team;
        }

        for (auto* team : strikeTeams) {
            delete team;
        }
    }
};


#endif //GAME_THEORY_GAME_MATCH_H
