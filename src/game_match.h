#ifndef GAME_THEORY_GAME_MATCH_H
#define GAME_THEORY_GAME_MATCH_H

#include <vector>
#include <memory>
#include "turn_action.h"

class ITurnAction;
class Team;

class MatchActionsFactory {
public:
    virtual std::vector<std::shared_ptr<ITurnAction>> Create() const = 0;
    virtual ~MatchActionsFactory() {} // Virtual destructor for polymorphism
};

class DefaultMatchActions : public MatchActionsFactory {
public:
    [[nodiscard]] std::vector<std::shared_ptr<ITurnAction>> Create() const override;
};

class GameMatch {
    /*
     *  Игровой матч состоящий из 14 ходов
     *  Содержит всю информацию о текущей игре, командах
     */
private:
    std::vector<Team*> teams;
    std::vector<Team*> strikeTeams;

    void setup_teams();
    void complete_turn();
    void compute_turn_results();

public:
    void start();
    void add_strike(Team *strikeTeam);
    ~GameMatch();
};


#endif //GAME_THEORY_GAME_MATCH_H
