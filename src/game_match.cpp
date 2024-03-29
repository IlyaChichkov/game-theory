#include "game_match.h"
#include "team.h"
#include "turn_action.h"

void print(const std::string& s) {
    std::cout << s;
}

void printLn(const std::string& s) {
    std::cout << s << std::endl;
}

std::vector<std::shared_ptr<ITurnAction>> DefaultMatchActions::create() const  {
    std::vector<std::shared_ptr<ITurnAction>> actions;
    actions.push_back(std::make_shared<ProductionChange>(-10));
    actions.push_back(std::make_shared<ProductionChange>(-10));
    actions.push_back(std::make_shared<ProductionChange>(-20));
    actions.push_back(std::make_shared<ProductionChange>(-20));
    actions.push_back(std::make_shared<ProductionChange>(10));
    actions.push_back(std::make_shared<ProductionChange>(10));
    actions.push_back(std::make_shared<ProductionChange>(20));
    actions.push_back(std::make_shared<ProductionChange>(20));
    actions.push_back(std::make_shared<ProductionChange>(30));
    actions.push_back(std::make_shared<ProductionChange>(30));
    actions.push_back(std::make_shared<ProductionChange>(50));
    actions.push_back(std::make_shared<ProductionChange>(0));
    actions.push_back(std::make_shared<ProvokeStrike>());
    actions.push_back(std::make_shared<ProvokeStrike>());
    return actions;
}

GameMatch::GameMatch(std::shared_ptr<MatchActionsFactory> _matchActions) {
    matchActionsFactory = std::move(_matchActions);
    turnsCount = matchActionsFactory->create().size();
}

void GameMatch::setup_teams() {
    int initial_production = 250;

    if(teams_files.empty()) return;
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    int team_id = 0;
    for(int i = 0; i < teams_files.size(); ++i) {
        std::string filePath = teams_folder_path + "\\" + teams_files[i];
        if(luaL_dofile(L, filePath.c_str()) != 0) {
            fprintf(stderr, "Error executing Lua script: %s\n", lua_tostring(L, -1));
        }

        LuaRef teamData = getGlobal(L, "team");

        for(int j = 0; j < (int)teamData["count"]; ++j) {
            std::string teamName = teamData["name"].tostring() + " (" + std::to_string(j) + ")";
            teams.push_back(std::make_shared<Team>(team_id++, teamName, filePath));
        }
    }

    for (int i = 0; i < teams.size(); ++i) {
        auto team = teams.at(i);
        int team_id = team->ID();
        team->set_production(initial_production);
        auto actions = matchActionsFactory->create();
        for (const auto action: actions) {
            if(action->actionType == TurnActionType::ProductionChange) {
                std::shared_ptr<ProductionChange> pc = std::dynamic_pointer_cast<ProductionChange>(action);
                pc->set_owner(team_id);
            }
        }
        team->set_turn_actions(actions);
    }
}

void GameMatch::complete_turn() {
    CommonData cd{
            turnIndex,
            turnsCount,
    };

    for(const auto& team : this->teams) {
        team->before_turn();
    }

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    getGlobalNamespace(L).addFunction("print", print);
    getGlobalNamespace(L).addFunction("printLn", printLn);

    // Выполнение хода каждой команды
    for(const auto& team : this->teams) {
        TurnData turnData(team);
        turnData.teams = teams;
        turnData.commonData = cd;

        std::string filePath = team->filePath;
        if(luaL_dofile(L, filePath.c_str()) != 0) {
            fprintf(stderr, "Error executing Lua script: %s\n", lua_tostring(L, -1));
        }

        LuaRef selectAction = getGlobal(L, "getTurnAction");
        LuaRef selectedActionTable = selectAction(turnData.generate_lua_ref(L));

        int selectedActionIndex = 0;
        if (selectedActionTable.isTable()) {
            if(!selectedActionTable["index"].isNumber()) {
                std::cerr << "Lua turn action return error: Wrong action index type!";
            }
            selectedActionIndex = selectedActionTable["index"].cast<int>() - 1;

            std::shared_ptr<ITurnAction> selectedAction = team->turn_actions.at(selectedActionIndex);

            switch (selectedAction->actionType) {
                case TurnActionType::None:
                    break;
                case TurnActionType::ProductionChange:
                    break;
                case TurnActionType::Strike:
                    std::shared_ptr<ProvokeStrike> strike = std::dynamic_pointer_cast<ProvokeStrike>(selectedAction);
                    if(!selectedActionTable["target"].isNumber()) {
                        std::cerr << "Lua turn action return error: Wrong strike target type!";
                    }
                    int targetIndex = selectedActionTable["target"].cast<int>();
                    auto targetTeam = get_team_by_id(targetIndex);
                    if(targetTeam == nullptr) {
                        std::cerr << "Null pointer for strike target team";
                        break;
                    }
                    strike->set_target(targetTeam);
                    break;
            }

            selectedAction->complete(&turnData);

            auto& actions = team->turn_actions;
            actions.erase(std::remove(actions.begin(), actions.end(), selectedAction), actions.end());
        } else {
            std::cerr << "Lua turn action return error: Wrong return type, supposed to be table!";
        }
    }

    for(const auto& team : this->teams) {
        team->after_turn();
    }

    compute_turn_results();

    for(const auto& team : this->teams) {
        team->pay_production_cost();
        team->add_funds(get_income(team->get_production()));
    }
}

void GameMatch::compute_turn_results() {
    total_production = 0;
    if(teams.empty()) return;
    for(const auto& team : this->teams) {
        total_production += team->get_production();
    }
    int max_production = 1000;
    sell_price = (int)(70 * max_production / total_production);
}

int GameMatch::get_income(int production) {
    return (int)(production * sell_price);
}

void GameMatch::start() {
    teams_folder_path = std::filesystem::current_path().string() + "/teams";
    if(std::filesystem::exists(teams_folder_path)) {
        std::filesystem::directory_iterator it(teams_folder_path);

        for (auto& entry : it) {
            if (is_regular_file(entry)) {
                teams_files.push_back(entry.path().filename().string());
            }
        }

        for (const std::string& filename : teams_files) {
            std::cout << filename << std::endl;
        }
    } else {
        try {
            std::filesystem::create_directory(teams_folder_path);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error: Failed to create teams folder";
        }
    }

    print_match_configuration();

    if(this->teams_files.empty()) {
        std::cout << "|-------------- ERROR! --------------|"   << std::endl;
        std::cout << "| NO TEAM FILES LOADED. PLEASE PROVIDE "  << std::endl;
        std::cout << "| LUA SCRIPTS IN 'teams' FOLDER"          << std::endl;
        std::cout << "|------------------------------------|"   << std::endl;
        return;
    }

    setup_teams();
    for (int i = 0; i < turnsCount; ++i) {
        std::cout << "[TURN " << i << "]" << std::endl;
        complete_turn();
        print_turn_results();
        turnIndex++;
    }
    print_match_results();
}

void GameMatch::print_match_configuration() {
    if(loggingLevel < 1) return;
    std::cout << "|-------- MATCH CONFIGURATION -------|"   << std::endl;
    std::cout << "| TURNS COUNT: " << turnsCount            << std::endl;
    std::cout << "| LOADED TEAMS:"                          << std::endl;
    for(const auto& file : this->teams_files) {
        std::cout << "| " << file << std::endl;
    }
    std::cout << "|------------------------------------|"   << std::endl;
}

void GameMatch::print_turn_results() {
    if(loggingLevel < 1) return;
    std::cout << "|----------- TURN RESULTS -----------|" << std::endl;
    for(const auto& team : this->teams) {
        std::cout << "| [" << team->ID() << "] " << team->name << "; Prod: " << team->get_production() << " Funds: " << team->get_funds() << " (+" << team->funds_delta_per_turn << ")" << std::endl;
    }
    std::cout << "|------------------------------------|" << std::endl;
}

void GameMatch::print_match_results() {
    std::cout << "|----------- MATCH RESULTS ----------|" << std::endl;
    int max_production = 0;
    for(const auto& team : this->teams) {
        if(team->get_production() > max_production) {
            max_production = team->get_production();
        }
    }

    std::cout << "| Production Winners:" << std::endl;
    for(const auto& team : this->teams) {
        if(team->get_production() == max_production) {
            std::cout << "| [" << team->ID() << "] " << team->name << std::endl;
        }
    }

    int max_funds = 0;
    for(const auto& team : this->teams) {
        if(team->get_funds() > max_funds) {
            max_funds = team->get_funds();
        }
    }

    std::cout << "| Funds:" << std::endl;
    for(const auto& team : this->teams) {
        if(team->get_funds() == max_funds) {
            std::cout << "| [" << team->ID() << "] " << team->name << " - funds = " << team->get_funds() << " winner!" << std::endl;
        }
        else {
            std::cout << "| [" << team->ID() << "] " << team->name << " - funds = " << team->get_funds() << std::endl;
        }
    }

    std::cout << "|------------------------------------|" << std::endl;
}

std::shared_ptr<Team> GameMatch::get_team_by_id(int id) {
    for(const auto& team : this->teams) {
        if(team->ID() == id) {
            return team;
        }
    }
    return nullptr;
}

GameMatch::~GameMatch() = default;
