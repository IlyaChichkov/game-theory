#ifndef GAME_THEORY_BULL_TEAM_H
#define GAME_THEORY_BULL_TEAM_H

#include <iostream>
#include "../team.h"

class BullTeam : public Team {
public:
    explicit BullTeam(int _id);
    std::shared_ptr<ITurnAction> make_turn(TurnData match);
    ~BullTeam();
};

#endif //GAME_THEORY_BULL_TEAM_H
