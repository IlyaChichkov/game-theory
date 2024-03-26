#include <iostream>
#include <ctime>
#include "src/game_match.h"

int main() {
    srand(time(0));

    std::cout << "Game theory." << std::endl;
    GameMatch match;
    match.start();

    return 0;
}
