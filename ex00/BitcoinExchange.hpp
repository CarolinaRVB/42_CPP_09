/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:16:35 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/20 12:42:34 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <algorithm>
# include <fstream>
# include <cstdlib>
# include <iomanip>
# include <limits>
# include <set>
# include <sstream>

class BitcoinExchange {
    private:
        std::map<std::string, float>    _map;
        BitcoinExchange();
    
    public:
        BitcoinExchange(std::string file);
        BitcoinExchange(const BitcoinExchange& obj);
        BitcoinExchange& operator=(const BitcoinExchange& obj);
        
        ~BitcoinExchange();
        void    handle_input(char *input);
        void    print_map();
        int     wrong_dates(std::fstream &file, std::map<std::string, float> *_map);
        int     save_file(std::fstream &file);
        void    calculate_bitcoin(std::map<std::string, float>::iterator iterator, std::string date, std::string value);

};

int     invalid_entry(std::string line, std::string *date, std::string *valueString, std::string sep, bool print);
int     invalid_date(std::string date, bool print);
int     invalid_value(std::string value, bool print);
int     check_set(char c, std::string set);


#endif