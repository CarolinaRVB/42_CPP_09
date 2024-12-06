/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:50:37 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/05 17:56:46 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "BitcoinExchange.hpp"
# include <fstream>

void    save_file(std::fstream &file, std::map<std::string, float> map) {
    std::string line;

    while (!file.eof()) {
        getline(file, line);
    }
}

int main(int argc, char **argv) {
    
    std::fstream file;

    if (argc == 1)
        std::cout << "Error: could not open file\n";
    file.open(argv[1], std::fstream::in);
    if (file.fail())
        std::cout << "Error: could not open file\n";

    std::map<std::string, float>    map;
    save_file(file, map);
}