
#include "Weapon.hpp"

Weapon::Weapon(/* args */)
{
}
Weapon(std::string name)
{
    this->type = name;
}

Weapon::~Weapon()
{
}

void Weapon::setType ( std::string const weapon_type)
{
    this->type = weapon_type;
}