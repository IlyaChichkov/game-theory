#ifndef GAME_THEORY_LUA_SERIALIZE_H
#define GAME_THEORY_LUA_SERIALIZE_H

#include <iostream>
#include <string>
#include <vector>
#include "turn_action.h"
#include "turn_data.h"

void print(const std::string& s) {
    std::cout << s;
}

void printLn(const std::string& s) {
    std::cout << s << std::endl;
}

struct LuaActions {
    lua_State* L;
    std::map<int, std::shared_ptr<ITurnAction>> my_actions;

    LuaRef get_all() {
        LuaRef v(L);
        v = newTable(L);
        int listCount = 0;
        for (const auto &a : my_actions) {
            v[listCount + 1] = newTable(L);
            v[listCount + 1]["id"] = a.first;
            v[listCount + 1]["type"] = (int)a.second->actionType;
            if(a.second->actionType == TurnActionType::ProductionChange){
                std::shared_ptr<ProductionChange> action = std::dynamic_pointer_cast<ProductionChange>(a.second);
                v[listCount + 1]["delta"] = action->get_delta();
            }

            listCount++;
        }
        return v;
    }

    LuaRef get_increase_production() {
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
        return v;
    }

    LuaRef get_decrease_production() {
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
        return v;
    }

    LuaRef get_production_change_by(int delta) {
        LuaRef v(L);
        v = newTable(L);
        for (const auto &a : my_actions) {
            if(a.second->actionType != TurnActionType::ProductionChange) continue;
            std::shared_ptr<ProductionChange> action = std::dynamic_pointer_cast<ProductionChange>(a.second);
            if(action->get_delta() == delta) {
                v["id"] = a.first;
                v["delta"] = action->get_delta();
                break;
            }
        }
        return v;
    }

    LuaRef get_provoke_strike() {
        LuaRef v(L);
        v = newTable(L);
        for (const auto &a : my_actions) {
            if(a.second->actionType != TurnActionType::Strike) continue;
            v["id"] = a.first;
            break;
        }
        return v;
    }
};

struct LuaTurnData {
    int teamId;
    int turn;
    int turnsCount;
    lua_State* L;
    LuaActions actions;
    std::vector<std::shared_ptr<Team>> teams;
    int (*get_expenses_at)(int production);
    int (*get_cost_at)(int production);

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

    int get_expenses(int production) {
        return get_expenses_at(production);
    }

    int get_cost(int production) {
        return get_cost_at(production);
    }
};

void luaApiRegistration(lua_State* L) {
    luaL_openlibs(L);
    luabridge::getGlobalNamespace(L)
            .beginClass<LuaActions>("LuaActions")
            .addFunction("all",                 &LuaActions::get_all)
            .addFunction("change_production",   &LuaActions::get_production_change_by)
            .addFunction("strike",              &LuaActions::get_provoke_strike)
            .addFunction("increase",            &LuaActions::get_increase_production)
            .addFunction("decrease",            &LuaActions::get_decrease_production)
            .endClass();
    luabridge::getGlobalNamespace(L)
            .beginClass<LuaTurnData>("LuaTurnData")
            .addProperty("id",              &LuaTurnData::teamId)
            .addProperty("turn",            &LuaTurnData::turn)
            .addProperty("turnsCount",      &LuaTurnData::turnsCount)
            .addFunction("opponents",       &LuaTurnData::get_opponents)
            .addFunction("expenses_at",     &LuaTurnData::get_expenses)
            .addFunction("cost_at",         &LuaTurnData::get_cost)
            .endClass();
    luabridge::getGlobalNamespace(L)
            .beginClass<Team>("Team")
            .endClass();
    luabridge::getGlobalNamespace(L)
            .beginClass<ITurnAction>("ITurnAction")
            .addFunction("type", &ITurnAction::getType)
            .endClass();
    luabridge::getGlobalNamespace(L)
            .deriveClass<ProductionChange, ITurnAction>("ProductionChange")
            .addFunction("get_delta", &ProductionChange::get_delta)
            .endClass();
    luabridge::getGlobalNamespace(L)
            .deriveClass<ProvokeStrike, ITurnAction>("ProvokeStrike")
            .endClass();
    getGlobalNamespace(L).addFunction("print", print);
    getGlobalNamespace(L).addFunction("printLn", printLn);
}

#endif //GAME_THEORY_LUA_SERIALIZE_H
