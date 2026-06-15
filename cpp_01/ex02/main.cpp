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

#include <iostream>
#include <string>

int main()
{
    std::string string = "HI THIS IS BRAIN";

    std::string *stringPTR = &string;
    std::string &stringREF = string;

    std::cout << std::endl << "Memory adresses" << std::endl << std::endl;

    std::cout << "The memory address of the string variable -> " << &string << std::endl;
    std::cout << "The memory address held by stringPTR      -> " << stringPTR << std::endl;
    std::cout << "The memory address held by stringREF      -> " << &stringREF << std::endl;
    std::cout << std::endl <<  "-------------------------------------------------------------" << std::endl;

    std::cout << std::endl << "Values" << std::endl << std::endl;
    std::cout << "The value of the string variable  -> " << string << std::endl;
    std::cout << "The value pointed to by stringPTR -> " << *stringPTR << std::endl;
    std::cout << "The value pointed to by stringREF -> " << stringREF << std::endl << std::endl;

    return (0);
}