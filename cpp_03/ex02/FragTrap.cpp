#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap("Default")
{
    hit_points = 100;
    energy_points = 100;
    attack_damage = 30;

    std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(const std::string& name) : ClapTrap(name)
{
    hit_points = 100;
    energy_points = 100;
    attack_damage = 30;

    std::cout << "FragTrap " << name << " constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other)
{
    std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other)
{
    std::cout << "FragTrap copy assignment operator called" << std::endl;

    if (this != &other)
    {
        ClapTrap::operator=(other);
    }

    return (*this);
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap " << name << " destructor called" << std::endl;
}

void FragTrap::highFivesGuys(void)
{
    std::cout << name << " requests a high five!" << std::endl;
}