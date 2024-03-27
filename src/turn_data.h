#ifndef GAME_THEORY_TURN_DATA_H
#define GAME_THEORY_TURN_DATA_H

#include <iostream>
#include <vector>
#include <memory>
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"

using namespace luabridge;

class Team;

class TurnData {
    /*
     *  Содержит всю информацию об игре, командах на
     *  текущем ходе игры
     */
private:
    std::shared_ptr<Team> receiveTeam;
public:
    TurnData(std::shared_ptr<Team> receiveTeam);
    std::vector<std::shared_ptr<Team>> teams;

    std::vector<std::shared_ptr<Team>> get_opponents(int team_id);

    LuaRef generate_lua_ref(lua_State* L);
};


#endif //GAME_THEORY_TURN_DATA_H
