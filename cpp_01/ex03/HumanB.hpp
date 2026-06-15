
#include <iostream>
#include "Weapon.hpp"

class HumanB
{
private:
    /* data */
    std::string name;
    Weapon weapon;
public:
    HumanB();
    HumanB::HumanB(std::string name);
    ~HumanB();
    void setWeapon(Weapon weapon);
    void attack();
};
