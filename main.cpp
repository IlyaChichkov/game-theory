#include <iostream>
#include <ctime>
#include "src/game_match.h"

void start_match(int &loggingLevel) {
    GameMatch match;
    match.loggingLevel = loggingLevel;
    match.start();
}

int main() {
    srand(time(0));

    int matchLoggingLevel = 2;

    int inputOption = 0;
    while(true) {
        std::cout << "|------------- MAIN MENU ------------|"   << std::endl;
        std::cout << "| Logging level:" << matchLoggingLevel    << std::endl;
        std::cout << "|------------------------------------|"   << std::endl;
        std::cout << "| (1) Start match"                        << std::endl;
        std::cout << "| (2) Change logging level"               << std::endl;
        std::cout << "| (0) Exit"                               << std::endl;
        std::cout << "|------------------------------------|"   << std::endl;

        std::cin >> inputOption;

        switch(inputOption) {
            case 0:
                return 0;
            case 1:
                start_match(matchLoggingLevel);
                break;
            case 2:
                std::cout << "Select logging level:"   << std::endl;
                std::cout << "0) Match results"   << std::endl;
                std::cout << "1) Turns log"   << std::endl;
                std::cout << "2) Turns detailed log"   << std::endl;
                std::cin >> matchLoggingLevel;
                break;
            default:
                break;
        }

    }
    return 0;
}
