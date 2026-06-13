/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:56:14 by yel-moha          #+#    #+#             */
/*   Updated: 2026/06/10 17:56:24 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie
{
    private:
        std::string name;

    public:
        void announce( void );
        void setName(std::string z_name);
        std::string getName(void);
        Zombie();
        //Zombie(std::string name);
        ~Zombie();
};

Zombie* zombieHorde( int N, std::string name );

#endif