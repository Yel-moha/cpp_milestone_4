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
    std::cout << getName() << ": BraiiiiiiinnnzzzZ..." << std::endl; 
}
Zombie::Zombie()
{
    std::cout << "Constructur of a zombie: " << getName() << std::endl;
}
Zombie::Zombie(std::string name)
{
    this->name = name;
    std::cout << "Constructur with a parameter of a zombie: " << getName() << std::endl;
}

std::string Zombie::getName(void)
{
    return(this->name);
}
Zombie::~Zombie()
{
    std::cout << "Zombie destroyed" << std::endl;
}

