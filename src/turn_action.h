#ifndef GAME_THEORY_TURN_ACTION_H
#define GAME_THEORY_TURN_ACTION_H

#include <utility>
#include "game_match.h"
#include "turn_data.h"

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
    virtual void Complete(TurnData *turnData) const = 0;
    virtual ~ITurnAction() {}
};

class ProductionChange : public ITurnAction {
private:
    int owner_id;
    int delta = 0;
public:
    explicit ProductionChange(int _delta);
    void SetOwner(int _owner_id);
    int GetDelta();
    void Complete(TurnData *turnData) const override;
};

class ProvokeStrike : public ITurnAction {
private:
    Team *strikeTarget = nullptr;
public:
    explicit ProvokeStrike();
    void Complete(TurnData *turnData) const override;
    void SetTarget(Team *target) ;
};

#endif //GAME_THEORY_TURN_ACTION_H
