#ifndef GAME_THEORY_LUA_SERIALIZE_H
#define GAME_THEORY_LUA_SERIALIZE_H

#include <iostream>
#include <string>
#include <vector>
#include "turn_action.h"
#include "turn_data.h"

struct LuaActions {
    lua_State* L;
    std::map<int, std::shared_ptr<ITurnAction>> my_actions;

    LuaRef get(int i) {
        LuaRef v(L);
        v = newTable(L);
        v["id"] = i;
        return v;
    }

    LuaRef get_all() {
        LuaRef v(L);
        v = newTable(L);
        int listCount = 0;
        for (const auto &a : my_actions) {
            v[listCount + 1] = newTable(L);
            v[listCount + 1]["id"] = a.first;
            v[listCount + 1]["type"] = (int)a.second->actionType;
            listCount++;
        }
        return v;
    }

    LuaRef get_incr() {
        LuaRef v(L);
        v = newTable(L);
        int listCount = 0;
        for (const auto &a : my_actions) {
            if(a.second->actionType != TurnActionType::ProductionChange) continue;
            std::shared_ptr<ProductionChange> action = std::dynamic_pointer_cast<ProductionChange>(a.second);
            if(action->get_delta() > 0) {
                v[listCount + 1] = newTable(L);
                v[listCount + 1]["id"] = a.first;
                v[listCount + 1]["delta"] = action->get_delta();
                listCount++;
            }
        }
        // v["size"] = listCount;
        return v;
    }

    LuaRef get_decr() {
        LuaRef v(L);
        v = newTable(L);
        int listCount = 0;
        for (const auto &a : my_actions) {
            if(a.second->actionType != TurnActionType::ProductionChange) continue;
            std::shared_ptr<ProductionChange> action = std::dynamic_pointer_cast<ProductionChange>(a.second);
            if(action->get_delta() <= 0) {
                v[listCount + 1] = newTable(L);
                v[listCount + 1]["id"] = a.first;
                v[listCount + 1]["delta"] = action->get_delta();
                listCount++;
            }
        }
        // v["size"] = listCount;
        return v;
    }

    LuaRef get_prod_change(int val) {
        LuaRef v(L);
        v = newTable(L);
        for (const auto &a : my_actions) {
            if(a.second->actionType != TurnActionType::ProductionChange) continue;
            std::shared_ptr<ProductionChange> action = std::dynamic_pointer_cast<ProductionChange>(a.second);
            if(action->get_delta() == val) {
                v["index"] = a.first;
                v["delta"] = action->get_delta();
                break;
            }
        }
        return v;
    }

    LuaRef get_strike() {
        LuaRef v(L);
        v = newTable(L);
        for (const auto &a : my_actions) {
            if(a.second->actionType != TurnActionType::Strike) continue;
            v["index"] = a.first;
            break;
        }
        return v;
    }
};

struct LuaTurnData {
    int teamId;
    lua_State* L;
    LuaActions actions;
    std::vector<std::shared_ptr<Team>> teams;

    LuaRef get_opponents() {
        LuaRef v(L);
        v = newTable(L);
        int listCount = 0;
        for (const auto &a : teams) {
            if(a->ID() == teamId) continue;
            v[listCount + 1] = newTable(L);
            v[listCount + 1]["id"] = a->ID();
            v[listCount + 1]["production"] = a->get_production();
            v[listCount + 1]["funds"] = a->get_funds();
            listCount++;
        }
        return v;
    }
};

#endif //GAME_THEORY_LUA_SERIALIZE_H
