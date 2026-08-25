/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:30:00 by yel-moha          #+#    #+#             */
/*   Updated: 2026/06/17 14:30:00 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

static int getLevel(std::string level)
{
    std::string levels[4] = {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR"
    };

    for (int i = 0; i < 4; i++)
    {
        if (level == levels[i])
            return (i);
    }
    return (-1);
}

int main(int argc, char **argv)
{
    Harl        harl;
    std::string level;

    if (argc != 2)
    {
        std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
        return (0);
    }
    level = argv[1];
    switch (getLevel(level))
    {
        case 0:
            std::cout << "[ DEBUG ]" << std::endl;
            harl.complain("DEBUG");
        case 1:
            std::cout << "[ INFO ]" << std::endl;
            harl.complain("INFO");
        case 2:
            std::cout << "[ WARNING ]" << std::endl;
            harl.complain("WARNING");
        case 3:
            std::cout << "[ ERROR ]" << std::endl;
            harl.complain("ERROR");
            break ;
        default:
            std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
            break ;
    }
    return (0);
}
