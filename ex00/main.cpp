/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:50:37 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/26 11:05:38 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "BitcoinExchange.hpp"

int main(int argc, char **argv) {

    if (argc != 2){
        std::cout << "Error: invalid arguments.\n";
        return 1;
    }
    try {
        BitcoinExchange btc("data.csv");
        btc.handle_input(argv[1]);
    }
    catch (std::exception &e) {
        std::cout << e.what() << "\n";
    }
       
    return 0;
}