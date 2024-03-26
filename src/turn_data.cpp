//
// Created by IlyaChichkov on 25.03.2024.
//

#include "turn_data.h"
#include "team.h"

std::vector<std::shared_ptr<Team>> TurnData::get_opponents(int team_id) {
    std::vector<std::shared_ptr<Team>> opponents;
    for (const auto team : teams) {
        if(team->ID() != team_id) {
            opponents.push_back(team);
        }
    }
    return opponents;
}
