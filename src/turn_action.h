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
public:
    int delta = 0;

    explicit ProductionChange(int _delta) {
        actionType = TurnActionType::ProductionChange;
        delta = _delta;
    }
};

class ProvokeStrike : public ITurnAction {
public:
    Team *strikeTarget = nullptr;

    explicit ProvokeStrike() {
        actionType = TurnActionType::Strike;
        strikeTarget = nullptr;
    }

    void SetTarget(Team *target) {
        strikeTarget = target;
    }
};

#endif //GAME_THEORY_TURN_ACTION_H
