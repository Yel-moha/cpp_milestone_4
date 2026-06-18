#include "HumanB.hpp"


HumanB::HumanB()
{
}
HumanB::HumanB(std::string name)
{
    this->name = name;
}
HumanB::~HumanB()
{
}

void HumanB::setWeapon(Weapon& weapon)
{
    this->weapon = &weapon;
}


void HumanB::attack()
{
    if(this->weapon != NULL)
        std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
    else
        std::cout << this->name << " I can't attack with no weapon" << std::endl;
}

