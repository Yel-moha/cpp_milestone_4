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
    randomChump("Brutto");
    Zombie *zom = newZombie("Bello");

    zom->announce();
    delete(zom);

}