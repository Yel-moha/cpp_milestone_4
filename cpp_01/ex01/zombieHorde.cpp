/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 11:07:31 by yel-moha          #+#    #+#             */
/*   Updated: 2026/06/15 11:07:36 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name )
{
    if(N > 0)
    {
        Zombie *horde = new Zombie[N];
        for(int i = 0; i < N; i++)
            horde[i].setName(name);
        return(horde);
    }
    else
    {
        std::cout << "N can not be less than 0" << std::endl;
        return (NULL);
    }
}