#include "team.h"


Team::Team()
{
    this->production = 250;

    this->options.push_back(STRIKE);
    this->options.push_back(STRIKE);
    this->options.push_back(SKIP);
    this->options.push_back(UP_10);
    this->options.push_back(UP_10);
    this->options.push_back(UP_20);
    this->options.push_back(UP_20);
    this->options.push_back(UP_20);
    this->options.push_back(UP_30);
    this->options.push_back(UP_30);
    this->options.push_back(UP_40);
    this->options.push_back(UP_50);
    this->options.push_back(DOWN_10);
    this->options.push_back(DOWN_20);
    this->options.push_back(DOWN_30);
}


int Team::get_prod() { 
    return this->production;
}


void Team::set_prod(int val) {
    this->production = val;
}


void Team::use_option(int opt, Team* target) {
    switch (opt)
    {
    case SKIP:
        del_opt(SKIP);
        break;

    case UP_10:
        set_prod(get_prod() + 10);
        del_opt(UP_10);

    case UP_20:
        set_prod(get_prod() + 20);
        del_opt(UP_20);

    case UP_30:
        set_prod(get_prod() + 30);
        del_opt(UP_30);

    case UP_40:
        set_prod(get_prod() + 40);
        del_opt(UP_40);

    case UP_50:
        set_prod(get_prod() + 50);
        del_opt(UP_50);

    case DOWN_10:
        set_prod(get_prod() - 10);
        del_opt(DOWN_10);

    case DOWN_20:
        set_prod(get_prod() - 20);
        del_opt(DOWN_20);

    case DOWN_30:
        set_prod(get_prod() - 30);
        del_opt(DOWN_30);

    case STRIKE:
        del_opt(STRIKE);
        if (target) {
            if (get_prod() > 199)
                target->set_prod(get_prod() / 2);
            else
                target->set_prod(100);
        }// TODO: Refuse any options for target of strike
        else
            std::cerr << __FILE__ << " in " << __LINE__ << ": Target of STRIKE not identified\n";
    default:
        std::cerr << __FILE__ << " in " << __LINE__ << ": Wrong option\n";
    }
}


void Team::del_opt(int val) {
    for (std::vector<int>::iterator it = options.begin(); it != options.end();) {
        if (*it == val) {
            options.erase(it);
            return;
        }
    }
    std::cerr << __FILE__ << " in " << __LINE__ << ": Use of absent option\n";
}