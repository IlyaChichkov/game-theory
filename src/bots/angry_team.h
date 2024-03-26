#ifndef GAME_THEORY_ANGRY_TEAM_H
#define GAME_THEORY_ANGRY_TEAM_H


#include <iostream>
#include <string>
#include "../team.h"

class AngryTeam : public Team {
public:
    explicit AngryTeam(int _id);
    explicit AngryTeam(int _id, std::string _name);
    std::shared_ptr<ITurnAction> make_turn(TurnData match);
    ~AngryTeam();
};

#endif //GAME_THEORY_ANGRY_TEAM_H
