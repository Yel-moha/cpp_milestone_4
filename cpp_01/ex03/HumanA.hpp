
#include <iostream>
#include "Weapon.hpp"

class HumanA
{
private:
    /* data */
    std::string name;
    Weapon weapon;
public:
    HumanA();
    HumanA(std::string name, Weapon weapon);
    ~HumanA();
    void setWeapon (Weapon weapon);
    void attack();
};
