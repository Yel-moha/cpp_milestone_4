#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
    : ClapTrap()
{
    this->hit_points = 100;
    this->energy_points = 50;
    this->attack_damage = 20;
    std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(const std::string& name)
    : ClapTrap(name)
{
    this->hit_points = 100;
    this->energy_points = 50;
    this->attack_damage = 20;
    std::cout << "ScavTrap " << this->name << " constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other)
    : ClapTrap(other)
{
    std::cout << "ScavTrap copy constructor called" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
    std::cout << "ScavTrap copy assignment operator called" << std::endl;
    if (this != &other)
        ClapTrap::operator=(other);
    return (*this);
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap " << this->name << " destructor called" << std::endl;
}

void ScavTrap::attack(const std::string& target)
{
    if (this->hit_points <= 0 || this->energy_points <= 0)
    {
        std::cout << "ScavTrap " << this->name << " cannot attack" << std::endl;
        return;
    }
    --this->energy_points;
    std::cout << "ScavTrap " << this->name << " attacks " << target
              << ", causing " << this->attack_damage << " points of damage!"
              << std::endl;
}

void ScavTrap::guardGate()
{
    std::cout << "ScavTrap " << this->name
              << " is now in Gate keeper mode" << std::endl;
}
