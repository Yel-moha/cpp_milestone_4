#include "ScavTrap.hpp"

int main()
{
    ScavTrap scavtrap("SC4V-TP");
    ScavTrap copy(scavtrap);
    ScavTrap assigned;

    assigned = scavtrap;
    scavtrap.attack("a vault hunter");
    scavtrap.takeDamage(42);
    scavtrap.beRepaired(20);
    scavtrap.guardGate();
    scavtrap.takeDamage(200);
    scavtrap.attack("a vault hunter");
    scavtrap.beRepaired(5);
    return (0);
}
