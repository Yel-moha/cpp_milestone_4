/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:16:53 by yel-moha          #+#    #+#             */
/*   Updated: 2026/06/10 18:16:56 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
   
Zombie::Zombie()
{
    std::cout << "Constructur of a zombie: " << getName() << std::endl;
}
/*
Zombie::Zombie(std::string name)
{
    this->name = name;
    std::cout << "Constructur with a parameter of a zombie: " << getName() << std::endl;
}
*/

Zombie::~Zombie()
{
    std::cout << "Zombie destroyed" << std::endl;
}

Zombie* zombieHorde( int N, std::string name )
{
    Zombie *horde = new Zombie[N];

    for(int i = 0; i < N; i++)
    {
        horde[i].setName(name);
    }
    return(horde);
}

void Zombie::setName(std::string z_name)
{
    this->name = z_name;
}
void Zombie::announce( void )
{
    std::cout << getName() << std::endl; 
}

std::string Zombie::getName(void)
{
    return(this->name);
}