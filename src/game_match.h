#ifndef GAME_THEORY_GAME_MATCH_H
#define GAME_THEORY_GAME_MATCH_H

#include <vector>
#include <memory>
#include "team.h"
#include "my_team.h"
#include "turn_action.h"

class MatchActionsFactory {
public:
    virtual std::vector<ITurnAction*> Create() const = 0;
    virtual ~MatchActionsFactory() {} // Virtual destructor for polymorphism
};

class DefaultMatchActions : public MatchActionsFactory {
public:
    [[nodiscard]] std::vector<ITurnAction*> Create() const override {
        std::vector<ITurnAction*> actions;
        actions.push_back(new ProductionChange(-10));
        actions.push_back(new ProductionChange(-10));
        actions.push_back(new ProductionChange(10));
        actions.push_back(new ProductionChange(10));
        actions.push_back(new ProvokeStrike());
        return actions;
    }
};

class GameMatch {
    /*
     *  Игровой матч состоящий из 14 ходов
     *  Содержит всю информацию о текущей игре, командах
     */
};


#endif //GAME_THEORY_GAME_MATCH_H
