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
    const int num_zom = 5;
    Zombie *zom = zombieHorde(num_zom, "Foo");
    
    if(!zom)
        return (0);
    for(int i = 0; i < num_zom; i++)
        zom[i].announce();
    delete[] zom;
    return (0);
}