#ifndef GAME_THEORY_TURN_DATA_H
#define GAME_THEORY_TURN_DATA_H

#include <iostream>
#include <vector>
#include <memory>
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"

using namespace luabridge;

class Team;

struct TurnContainer {
    int price;
    int totalProduction;
    std::map<int, int> teamsProduction;
    std::map<int, int> teamsFunds;
};

class TurnData {
    /*
     *  Содержит всю информацию об игре, командах на
     *  текущем ходе игры
     */
private:
    std::shared_ptr<Team> receiveTeam;
public:
    int turn = 0;
    std::shared_ptr<TurnContainer> container;
    TurnData(int, std::shared_ptr<TurnContainer>);
    std::vector<std::shared_ptr<Team>> teams;
    LuaRef export_lua_table(lua_State* L);
};


#endif //GAME_THEORY_TURN_DATA_H
