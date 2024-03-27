#include <iostream>
#include <ctime>
#include "src/game_match.h"

int main() {
    srand(time(0));

    std::cout << "Game theory." << std::endl;
    GameMatch match;
    match.start();

    /*
    TODO: Простой пример работы с lua файлом

    #include "lua.hpp"
    #include "LuaBridge/LuaBridge.h"

    using namespace luabridge;

    void print(const std::string& s) {
        std::cout << s;
    }

    void printLn(const std::string& s) {
        std::cout << s << std::endl;
    }

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    getGlobalNamespace(L).addFunction("print", print);
    getGlobalNamespace(L).addFunction("printLn", printLn);

    if(luaL_dofile(L, "./file.lua") != 0) {
        fprintf(stderr, "Error executing Lua script: %s\n", lua_tostring(L, -1));

        int a = 0;
        std::cin >> a;
        return 1;
    }

    LuaRef v (L);
    v = newTable (L);

    v [1] = newTable (L);
    v [2] = newTable (L);
    v [3] = newTable (L);

    v [1]["name"] = std::string("Bull A");
    v [2]["name"] = std::string("Bull B");
    v [3]["name"] = std::string("Bull C");

    v [1]["production"] = 250;
    v [2]["production"] = 280;
    v [3]["production"] = 240;

    setGlobal(L, v, "teams");

    LuaRef selectedAction = getGlobal(L, "getTurnAction");
    int result = selectedAction();
    */

    return 0;
}
