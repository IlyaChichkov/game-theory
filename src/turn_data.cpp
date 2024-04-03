#include "turn_data.h"
#include "team.h"


TurnData::TurnData(int _turn, std::shared_ptr<TurnContainer> _container) {
    turn = _turn;
    container = _container;
}
