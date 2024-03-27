#ifndef GAME_THEORY_GAME_MATCH_H
#define GAME_THEORY_GAME_MATCH_H

#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include "turn_action.h"

class ITurnAction;
class Team;

class MatchActionsFactory {
public:
    virtual std::vector<std::shared_ptr<ITurnAction>> create() const = 0;
    virtual ~MatchActionsFactory() = default;
};

class DefaultMatchActions : public MatchActionsFactory {
public:
    [[nodiscard]] std::vector<std::shared_ptr<ITurnAction>> create() const override;
};

class GameMatch {
    /*
     *  Игровой матч состоящий из 14 ходов
     *  Содержит информацию о игре, командах, и т.д.
     *  Управляет циклом игры, производит ходы
     */
private:
    std::vector<std::shared_ptr<Team>> teams;
    std::vector<std::shared_ptr<Team>> strikeTeams;
    std::map<int, int> productsPriceTable;
    std::map<int, int> productionCostsTable;

    int total_production = 0;
    int sell_price = 0;

    void setup_teams();
    void complete_turn();
    int get_income(int production);
    void print_turn_results();
    void print_match_results();
    void compute_turn_results();

public:
    void start();

    ~GameMatch();
};


#endif //GAME_THEORY_GAME_MATCH_H
