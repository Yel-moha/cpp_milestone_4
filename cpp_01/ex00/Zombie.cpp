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
   
void Zombie::announce( void )
{
    std::cout << get_name() << "o: BraiiiiiiinnnzzzZ..." << std::endl; 
}
Zombie::Zombie()
{
    std::cout << "Constructur of a zombie: " << get_name() << std::endl;
}
void Zombie::put_name(std::string z_name)
{
    this->name = z_name;
}

std::string Zombie::get_name(void)
{
    return(this->name);
}

Zombie* newZombie( std::string name )
{
    Zombie *zom;

    zom = new Zombie;
    zom->put_name(name);
    return(zom);
}
void randomChump( std::string name ); // suppongo chiami la funzione sopra
