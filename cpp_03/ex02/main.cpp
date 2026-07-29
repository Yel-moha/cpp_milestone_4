#include "FragTrap.hpp"

int main()
{
	FragTrap frag("frag");

	frag.attack("Bandit");
	frag.takeDamage(20);
	frag.beRepaired(15);
	frag.highFivesGuys();

	return (0);
}