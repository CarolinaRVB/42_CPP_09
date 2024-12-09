/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:57:10 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/09 10:49:05 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "BitcoinExchange.hpp"

int check_set(char c, std::string set) {
    int i = 0;

    while (set[i]) {
        if (set[i] == c)
            return (0);
        i++;
    }
    return (1);
}

int    invalid_date(std::string date, bool print) {
    std::string set = "0123456789-";
    int i = 0;

    if (std::count(date.begin(), date.end(), '-')  != 2 || date.size() != 10
        || date[4] != '-' || date[7] != '-' ) {    
        std::cout << "Error: bad input => $" << date << "$\n";        
        return 1;
    }
    while (date[i]) {
        if (check_set(date[i], set)) {
            if (print)
                std::cout << "Error: bad input => " << date << "\n";        
            return (1);
        }
        i++;
    }
    return 0;
}


int    invalid_value(std::string value, bool print) {
    std::string doubles = "0123456789.";
    int i = 0;

    if (value[0] == '-' || value[0] == '.' || (value[value.length() - 1] == '.')) {
        if (print)
            std::cout << "Error: bad input => " << value << "\n";
        return (1);
    }
    while (value[i]) {
        if (check_set(value[i], doubles)) {
            if (print)
                std::cout << "Error: bad input => " << value << "\n";
            return (1);
        }
        i++;
    }
    return 0;
}


int invalid_entry(std::string line, std::string *date, float *value, std::string sep, bool print) {
    std::size_t separator = line.find(sep);
    if (separator == std::string::npos){
        if (print)
            std::cout << "Error: bad input => " << line << "\n";
        return 1;
    }

    if (print)
        separator--;
    *date = line.substr(0, separator);
    if (invalid_date(*date, print)) {
        return 1;
    }
    
    size_t start = separator + 1;
    if (print)
        start += 2;
    std::string valueString = line.substr(start, line.size());
    if (valueString.empty()) {
        if (print)
            std::cout << "Error: bad input => " << date << "\n";
        return 1;
    }
    *value = std::atof(valueString.c_str());
    if (*value >= std::numeric_limits<int>::max()) {
        std::cout << "Error: too large a number\n";
        return 1;
    }
    if (invalid_value(valueString, print))
        return 1;

    return 0;
}

int    save_file(std::fstream &file, std::map<std::string, float> *map) {
    std::string line;
    std::string date;
    float       value;
    long unsigned int counter = 0;

    getline(file, line);
    if (line != "date,exchange_rate")
        return 1;
    while (!file.eof()) {
        
        getline(file, line);
        if (!line.empty()) {
            if (invalid_entry(line, &date, &value, ",",false))
                return 1;
            
            (*map).insert(std::pair<std::string, float>(date, value));
            counter++;
        }
    }
    if ((*map).size() != counter)
        return 1;    
    return 0;
}

void    BitcoinExchange::print_map() {
    std::map<std::string, float>::iterator iterator;
    
    for (iterator = _map.begin(); iterator != _map.end(); ++iterator) {
        std::cout << "Map elements: " << iterator->first << ": " << std::fixed << std::setprecision(2) << iterator->second << "\n";
    }
}

void BitcoinExchange::handle_input(char *input) {
    std::fstream    file;
    std::string     line;
    std::string     date;
    float           value;
    std::map<std::string, float>::iterator iterator;

    file.open(input, std::fstream::in);
    if (file.fail())
        throw std::runtime_error("Error: failed to open input file");
    
    getline(file, line);
    if (line != "date | value") {
        std::cout << "Error: invalid input format\n";
        return ;
    }
    while (!file.eof()) {
        getline(file, line);
        if (!line.empty()) {
            if (invalid_entry(line, &date, &value, "|", true)){
                continue;
            }
            else {
                iterator = _map.find(date);
                if (iterator != _map.end()) {
                    float calc = iterator->second * value;
                    std::cout << date << " => " << value << " = "  << calc << "\n";
                }
                else {
                    std::cout << "Error: bad input => " << date << "\n";
                }
            }
        }
    }
        
}

BitcoinExchange::BitcoinExchange(std::string filename) {
    std::fstream file;
   
    file.open(filename.c_str(), std::fstream::in);
    if (file.fail())
        throw std::runtime_error("Error: failed to open database file");
    
    if (save_file(file, &_map) != 0) {
        file.close();
        throw std::runtime_error("Error: failed to save file");        
    };
    file.close(); 
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& obj) {    
    _map = obj._map;
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& obj) {
    if (this == &obj) return *this;
    _map = obj._map;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

