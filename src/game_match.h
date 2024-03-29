#ifndef GAME_THEORY_GAME_MATCH_H
#define GAME_THEORY_GAME_MATCH_H

#include <fstream>
#include <filesystem>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include "turn_action.h"
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"

using namespace luabridge;

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
    std::shared_ptr<MatchActionsFactory> matchActionsFactory;
    int turnIndex = 1;
    int turnsCount = 14;
    std::vector<std::shared_ptr<Team>> teams;
    std::vector<std::shared_ptr<Team>> strikeTeams;

    /*
     *  TODO: Добавить данные о общем производстве, текущей
     *        цене товара, таблицы зависимости издержек
     *        от производства, таблицы зависимости цены от
     *        общего производства
     */
    std::map<int, int> productsPriceTable;
    std::map<int, int> productionCostsTable;

    int total_production = 0;
    int sell_price = 0;

    std::string teams_folder_path;
    std::vector<std::string> teams_files;

    std::shared_ptr<Team> get_team_by_id(int id);
    void setup_teams();
    void complete_turn();
    int get_income(int production);
    void print_match_configuration();
    void print_turn_results();
    void print_match_results();
    void compute_turn_results();

public:
    GameMatch(std::shared_ptr<MatchActionsFactory> _matchActions);
    int loggingLevel = 0;
    void start();

    ~GameMatch();
};


#endif //GAME_THEORY_GAME_MATCH_H
