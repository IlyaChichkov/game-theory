#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <vector>

#define STRIKE  0
#define SKIP    1
#define UP_10   2
#define UP_20   3
#define UP_30   4
#define UP_40   5
#define UP_50   6
#define DOWN_10 7
#define DOWN_20 8
#define DOWN_30 9

class Team
{
private:
    int production;
    std::vector<int> options;
    void del_opt(int val);
public:
    Team();
    void set_prod(int val);
    int get_prod();
    void use_option(int opt, Team* target=NULL);
};

#endif // TEAM_H
