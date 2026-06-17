/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 18:22:12 by yel-moha          #+#    #+#             */
/*   Updated: 2026/06/17 10:49:16 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cerr << "Please insert those arguments in the following order: "
				  << "<filename> <s1 (string to find)> <s2 (string to replace)>"
				  << std::endl;
		return (1);
	}

	std::string filename = argv[1]; //C++98 std::ifstream non accetta direttamente una std::string
	std::string line;
	std::string result;
	std::string s1 = argv[2];
	std::string s2 = argv[3];
	size_t pos;
	size_t found;

	if (s1.empty())
	{
		std::cerr << "Error: s1 cannot be empty" << std::endl;
		return (1);
	}
	// apri argv[1] in lettura
	// std::ifstream significa input file stream: uno stream per leggere da un file.
	std::ifstream input(filename.c_str());// filename.c_str() restituisce il contenuto di quella stringa in formato compatibile con le funzioni/classi che vogliono un const char *
	//controllo se l'apertura e' andata a buon fine
	if(!input)
	{
		std::cerr << "Error: cannot open input file" << std::endl;
		return (1);
	}
	std::ofstream output((filename + ".replace").c_str()); //filename + ".replace" il nome del nuovo file con la sostituzione
	if(!output)
	{
		std::cerr << "Error: cannot create output file" << std::endl;
		return (1);
	}
	while (std::getline(input, line))
	{
		result = "";
		pos = 0;
		
		while ((found = line.find(s1, pos)) != std::string::npos)
		{
			result += line.substr(pos, found - pos);
			result += s2;
			pos = found + s1.length();
		}
		
		result += line.substr(pos);
		output << result;
		
		if (!input.eof())
			output << std::endl;
	}
	return (0);
}
