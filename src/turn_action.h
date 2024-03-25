#ifndef GAME_THEORY_TURN_ACTION_H
#define GAME_THEORY_TURN_ACTION_H

#include <utility>
#include "game_match.h"
#include "team.h"

class GameMatch;
class Team;

enum class TurnActionType {
    None,
    ProductionChange,
    Strike
};

class ITurnAction {
    /*
     *  Игровые действия выполняемые командами каждый ход
     *  (изменение продукции, забастовки)
     */
public:
    TurnActionType actionType = TurnActionType::None;
    virtual ~ITurnAction() {}
};

class ProductionChange : public ITurnAction {
private:
    int delta = 0;
public:
    explicit ProductionChange(int _delta) {
        actionType = TurnActionType::ProductionChange;
        delta = _delta;
    }
};

class ProvokeStrike : public ITurnAction {
private:
    Team *strikeTarget = nullptr;
public:
    explicit ProvokeStrike() {
        actionType = TurnActionType::Strike;
        strikeTarget = nullptr;
    }

    void SetTarget(Team *target) {
        strikeTarget = target;
    }
};

#endif //GAME_THEORY_TURN_ACTION_H
