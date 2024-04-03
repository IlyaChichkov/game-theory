#ifndef GAME_THEORY_TURN_ACTION_H
#define GAME_THEORY_TURN_ACTION_H

#include <utility>
#include "game_match.h"
#include "turn_data.h"

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
    int getType();
    virtual void complete(std::shared_ptr<TurnData> turnData) const = 0;
    virtual ~ITurnAction() {}
};

class ProductionChange : public ITurnAction {
private:
    int owner_id;
    int delta = 0;
public:
    explicit ProductionChange(int _delta);
    void set_owner(int _owner_id);
    int get_delta();
    void complete(std::shared_ptr<TurnData> turnData) const override;
};

class ProvokeStrike : public ITurnAction {
private:
    std::shared_ptr<Team> strikeTarget = nullptr;
public:
    explicit ProvokeStrike();
    void complete(std::shared_ptr<TurnData> turnData) const override;
    void set_target(std::shared_ptr<Team> target);
};

#endif //GAME_THEORY_TURN_ACTION_H
