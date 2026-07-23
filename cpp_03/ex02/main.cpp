#include "FragTrap.hpp"

int main()
{
	FragTrap frag("Jack");

	frag.attack("Bandit");
	frag.takeDamage(20);
	frag.beRepaired(15);
	frag.highFivesGuys();

	return (0);
}