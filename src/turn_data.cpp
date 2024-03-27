#include "turn_data.h"
#include "team.h"


TurnData::TurnData(std::shared_ptr<Team> _receiveTeam) {
    receiveTeam = _receiveTeam;
}

std::vector<std::shared_ptr<Team>> TurnData::get_opponents(int team_id) {
    std::vector<std::shared_ptr<Team>> opponents;
    for (const auto team : teams) {
        if(team->ID() != team_id) {
            opponents.push_back(team);
        }
    }
    return opponents;
}

LuaRef TurnData::generate_lua_ref(lua_State* L) {
    LuaRef v(L);
    v = newTable(L);
    // Данные о команде получателе
    v["this"] = newTable(L);
    v["this"]["name"] = receiveTeam->name;
    v["this"]["funds"] = receiveTeam->get_funds();
    v["this"]["production"] = receiveTeam->get_production();
    v["this"]["actions"] = newTable(L);
    v["this"]["actions_count"] = receiveTeam->turn_actions.size();

    for (int i = 0; i < receiveTeam->turn_actions.size(); ++i) {
        const auto &action = receiveTeam->turn_actions[i];
        v["this"]["actions"][i] = newTable(L);
        v["this"]["actions"][i]["id"] = (int)(i);
        v["this"]["actions"][i]["type"] = (int)(action->actionType);
        switch (action->actionType) {
            case TurnActionType::None:
                std::cerr << "Error: Action type set to None!\n";
                break;
            case TurnActionType::ProductionChange:
                std::shared_ptr<ProductionChange> pc = std::dynamic_pointer_cast<ProductionChange>(action);
                v["this"]["actions"][i]["delta"] = (int)(pc->get_delta());
                break;
        }
    }

    // Данные об оппонентах
    v["opponents"] = newTable(L);
    v["opponents_count"] = teams.size();
    for (int i = 0; i < teams.size(); ++i) {
        v["opponents"][i] = newTable(L);
        v["opponents"][i]["production"] = teams.at(i)->get_production();
        v["opponents"][i]["funds"] = teams.at(i)->get_funds();
    }

    // Общие данные

    //v["this"][""] = std::string("hi");
    return v;
}

