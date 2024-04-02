#include "utils.h"

int Utils::get_rand_int(int from, int to) {
    return std::rand() % (to - from) + from;
}
