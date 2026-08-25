/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:22:27 by yel-moha          #+#    #+#             */
/*   Updated: 2026/03/12 16:50:06 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int ac, char **av)
{
    int     i;
    int     j;
    char    c;
    
    i = 1;
    if(ac == 1)
        std::cout<<"* LOUD AND UNBEARABLE FEEDBACK NOISE *";
    while(i <=(ac - 1))
    {
        j = 0;
        while(av[i][j])
        {
           c = std::toupper(av[i][j]);
           std::cout << c;
           j++;
        }
        i++;
    }
    std::cout << std::endl;
    return (0);
}