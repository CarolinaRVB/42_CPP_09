/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:16:35 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/09 10:47:02 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <algorithm>
# include <fstream>
# include <map>
# include <cstdlib>
# include <iomanip>
# include <limits>
# include <set>
# include <sstream>
/*
    Can create a class that has a map container
    One of the constructors will receive a char * (database.csv) -> to build
    map of dataset
    Can have method to print dataset
    Can have method to process input text to retrieve required bitcoin prices -> void
    function that simply processes and prints line by line

    OR

    can simply have file that has functions

*/

class BitcoinExchange {
    private:
        std::map<std::string, float>    _map;
        BitcoinExchange();
    
    public:
        BitcoinExchange(std::string file); // builds and checks file
        BitcoinExchange(const BitcoinExchange& obj);
        BitcoinExchange& operator=(const BitcoinExchange& obj);
        
        ~BitcoinExchange();
        void    handle_input(char *input);
        void    print_map();

};

#endif