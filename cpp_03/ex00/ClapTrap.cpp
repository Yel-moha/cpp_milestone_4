#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void)
    : name("default"), hit_points(10), energy_points(10), attack_damage(0)
{
    std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string& name)
    : name(name), hit_points(10), energy_points(10), attack_damage(0)
{
    std::cout << "ClapTrap " << this->name << " constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

ClapTrap &ClapTrap::operator=( const ClapTrap &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
    {
        this->name = other.name;
        this->hit_points = other.hit_points;
        this->energy_points = other.energy_points;
        this->attack_damage = other.attack_damage;
    }
    return (*this);
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap " << this->name << " destructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
    if (this->hit_points <= 0 || this->energy_points <= 0)
    {
        std::cout << "ClapTrap " << this->name << " cannot attack" << std::endl;
        return;
    }
    --this->energy_points;
    std::cout << "ClapTrap " << this->name << " attacks " << target
              << ", causing " << this->attack_damage << " points of damage!"
              << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (this->hit_points <= 0)
    {
        std::cout << "ClapTrap " << this->name << " is already destroyed"
                  << std::endl;
        return;
    }
    if (amount >= static_cast<unsigned int>(this->hit_points))
        this->hit_points = 0;
    else
        this->hit_points -= amount;
    std::cout << "ClapTrap " << this->name << " takes " << amount
              << " points of damage and has " << this->hit_points
              << " hit points left" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->hit_points <= 0 || this->energy_points <= 0)
    {
        std::cout << "ClapTrap " << this->name << " cannot be repaired"
                  << std::endl;
        return;
    }
    --this->energy_points;
    this->hit_points += amount;
    std::cout << "ClapTrap " << this->name << " repairs itself for " << amount
              << " hit points and now has " << this->hit_points
              << " hit points" << std::endl;
}
