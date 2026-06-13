/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 19:38:50 by yel-moha          #+#    #+#             */
/*   Updated: 2026/06/12 19:38:52 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{

    Zombie *zom = zombieHorde(5, "Foo");
    
    for(int i = 0; i < 5; i++)
    {
        zom[i].announce();
    }
    delete[]zom;
    return (0);
}