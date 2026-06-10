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
        void put_name(std::string z_name);
        std::string get_name(void);
        Zombie();
        ~Zombie();
    
};

Zombie* newZombie( std::string name ); //funzione sopra
void randomChump( std::string name ); // suppongo chiami la funzione sopra


#endif