#include "game_match.h"
#include "team.h"
#include "turn_action.h"
#include "lua_serialize.h"

double income_func(double x, double u, double h) {
    const double constant_term = 100000 / (h * std::sqrt(2 * 3.1415));
    double exponent = std::pow(x - u, 2) / (2 * std::pow(h, 2.5));
    return constant_term * std::exp(exponent);
}

double square_func(double x, double a, double b, double c) {
    double inner_term = std::pow(x - 700 - b, 2) / std::pow(c, 2);
    double exponent = std::exp(inner_term);
    return 200 + a * exponent;
}

double expenses_func(double x, double u, double h) {
    return square_func(x, 6, 0, 171)*0.5+0.1*-income_func(x, 700, 100);
}

int GameMatch::get_expenses(int production) {
    return (int)(expenses_func(production, 700, 100));
}

int GameMatch::get_product_cost(int total_production) {
    return (int)(income_func(total_production, 700, 100));
}

int GameMatch::get_income(int production) {
    return (int)(production * sell_price);
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

    // Load teams options from teams folder
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

    // Prepare teams objects
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

void report_errors(lua_State *luaState, int status) {
    if (status == 0) {
        return;
    }

    std::cerr << "[LUA ERROR] " << lua_tostring(luaState, -1) << std::endl;

    // Remove error message from Lua state
    lua_pop(luaState, 1);
}

void GameMatch::complete_turn() {
    for(const auto& team : this->teams) {
        team->before_turn();
    }

    // Loop through teams and perform selected action
    for(const auto& team : this->teams) {
        lua_State* L = luaL_newstate();
        luaApiRegistration(L);

        std::string filePath = team->filePath;
        int luaStatus = luaL_dofile(L, filePath.c_str());

        report_errors(L, luaStatus);

        LuaTurnData tD;
        tD.L = L;
        tD.teamId = team->ID();
        tD.teams = teams;
        tD.turn = turnIndex;
        tD.turnsCount = turnsCount;
        tD.get_expenses_at = get_expenses;
        tD.get_cost_at = get_product_cost;

        LuaActions am;
        am.L = L;
        for (int i = 0; i < team->turn_actions.size(); ++i) {
            am.my_actions[i] = team->turn_actions.at(i);
        }

        setGlobal(L, tD, "data");
        setGlobal(L, am, "actions");

        complete_action(L, team);
    }

    for(const auto& team : this->teams) {
        team->after_turn();
    }

    compute_turn_results();

    for(const auto& team : this->teams) {
        int p = team->get_production();
        team->add_funds(get_income(p) - get_expenses(p));
    }
}

void GameMatch::complete_action(lua_State* L, std::shared_ptr<Team> team) {
    TurnData turnData(team);
    turnData.teams = teams;

    LuaRef selectAction = getGlobal(L, "getTurnAction");
    LuaRef selectedActionTable = nullptr;

    enableExceptions(L);
    try {
        selectedActionTable = selectAction();
    }
    catch (const luabridge::LuaException &e) {
        std::cerr << e.what() << std::endl;
        teamFileHasErrors = true;
        return;
    }

    int selectedActionIndex = 0;
    if (selectedActionTable.isTable()) {
        if(!selectedActionTable["index"].isNumber()) {
            std::cerr << "Error: Wrong action index type! (supposed to be number)" << std::endl;
            teamFileHasErrors = true;
            return;
        }
        selectedActionIndex = selectedActionTable["index"].cast<int>();

        std::shared_ptr<ITurnAction> selectedAction = team->turn_actions.at(selectedActionIndex);

        switch (selectedAction->actionType) {
            case TurnActionType::None:
                break;
            case TurnActionType::ProductionChange:
                break;
            case TurnActionType::Strike:
                std::shared_ptr<ProvokeStrike> strike = std::dynamic_pointer_cast<ProvokeStrike>(selectedAction);
                if(!selectedActionTable["target"].isNumber()) {
                    std::cerr << "Lua turn action return error: Wrong strike target type! (supposed to be number)" << std::endl;
                    teamFileHasErrors = true;
                    return;
                }
                int targetIndex = selectedActionTable["target"].cast<int>();
                auto targetTeam = get_team_by_id(targetIndex);
                if(targetTeam == nullptr) {
                    std::cerr << "Error: Null pointer for strike target team!" << std::endl;
                    teamFileHasErrors = true;
                    return;
                }
                strike->set_target(targetTeam);
                break;
        }

        selectedAction->complete(&turnData);

        auto& actions = team->turn_actions;
        actions.erase(std::remove(actions.begin(), actions.end(), selectedAction), actions.end());
    } else {
        std::cerr << "Error: Wrong return type from lua 'getTurnAction' function, supposed to be table!" << std::endl;
        teamFileHasErrors = true;
        return;
    }
}

void GameMatch::compute_turn_results() {
    total_production = 0;
    if(teams.empty()) return;
    for(const auto& team : this->teams) {
        total_production += team->get_production();
    }
    sell_price = get_product_cost(total_production);
}

void GameMatch::start() {
    // Check teams folder & load teams
    teams_folder_path = std::filesystem::current_path().string() + teamsFolder;
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
        if(teamFileHasErrors) {
            std::cout << "|-------------- ERROR! --------------|"   << std::endl;
            std::cout << "| ONE OF THE LUA SCRIPTS HAS ERRORS"  << std::endl;
            std::cout << "|------------------------------------|"   << std::endl;
            return;
        }
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
        if(team->funds_delta_per_turn >= 0) {
            std::cout << "| [" << team->ID() << "] " << team->name << "; Prod: " << team->get_production() << " Funds: " << team->get_funds() << " (+" << team->funds_delta_per_turn << ")" << std::endl;
        } else {
            std::cout << "| [" << team->ID() << "] " << team->name << "; Prod: " << team->get_production() << " Funds: " << team->get_funds() << " (" << team->funds_delta_per_turn << ")" << std::endl;
        }
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
