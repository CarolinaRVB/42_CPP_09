/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:50:37 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/09 14:47:58 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "BitcoinExchange.hpp"

/*
    std::map is implemented as a binary search tree, which ensures that the
    elements are always sorted based on their keys. This sorted structure
    allows for efficient searching, insertion, and deletion of elements,
    making std::map a popular choice when fast key-based operations are required.
*/

int main(int argc, char **argv) {

    if (argc == 1)
        std::cout << "Error: could not open file\n";
    
    try {
        BitcoinExchange btc("data.csv");
        btc.handle_input(argv[1]);
    }
    catch (std::exception &e) {
        std::cout << e.what() << "\n";
    }
       
    return 0;
}