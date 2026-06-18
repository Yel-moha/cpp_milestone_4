#ifndef HUMAN_B_HPP
# define HUMAN_B_HPP

#include <iostream>
#include "Weapon.hpp"

class HumanB
{
private:
    /* data */
    std::string name;
    Weapon* weapon;
public:
    HumanB();
    HumanB(std::string weapon);
    ~HumanB();
    void setWeapon(Weapon& weapon);
    void attack();
};

# endif