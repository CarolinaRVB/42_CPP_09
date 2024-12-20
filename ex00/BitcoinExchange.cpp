/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:57:10 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/20 17:17:49 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string filename) {
    std::fstream file;
   
    file.open(filename.c_str(), std::fstream::in);
    if (file.fail())
        throw std::runtime_error("Error: failed to open database file");
    
    if (save_file(file) != 0) {
        file.close();
        throw std::runtime_error("Error: failed to save file");        
    };
    file.close();
    file.open(filename.c_str(), std::fstream::in);
    if (file.fail())
        throw std::runtime_error("Error: failed to open database file");
    
    if (wrong_dates(file, &_map) != 0) {
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
    std::string     value;
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
                    calculate_bitcoin(iterator, date, value);
                }
                else {
                    iterator = _map.lower_bound(date);
                    if (iterator != _map.begin())
                        iterator--;
                    calculate_bitcoin(iterator, date, value);
                }
            }
        }
    }   
}

int BitcoinExchange::wrong_dates(std::fstream &file, std::map<std::string, float> *_map) {
    std::string       line;
    std::string       date;
    std::map<std::string, float>::iterator  iter;

    getline(file, line);
    iter = _map->begin();
    while (!file.eof()) {
        getline(file, line);
        if (!line.empty()) {
            date = line.substr(0, 10);
            if (date != iter->first)
                return 1;
            iter++;
        }
    }
    return 0;
}

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
    if (std::atoi(date.substr(0, 4).c_str()) < 2009
        || std::atoi(date.substr(0, 4).c_str()) > 2024
        || std::atoi(date.substr(5, 2).c_str()) > 12
        || date.substr(5,2) == "00"
        || std::atoi((date.substr(8, 2)).c_str()) > 31
        || date.substr(8,2) == "00")
    {
        if (print)
            std::cout << "Error: bad input => " << date << "\n";
        return (1);
    }
    return 0;
}

int    invalid_value(std::string value, bool print) {
    std::string doubles = "0123456789.";
    int i = 0;

    if (value[0] == '-') {
        std::cout << "Error: not a positive number.\n";
        return (1);
    }
    if (value[0] == '.' || (value[value.length() - 1] == '.') 
        || std::count(value.begin(), value.end(), '.') > 1) {
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

int invalid_entry(std::string line, std::string *date, std::string *valueString, std::string sep, bool print) {
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
    *valueString = line.substr(start, line.size());
    if ((*valueString).empty()) {
        if (print)
            std::cout << "Error: bad input => " << date << "\n";
        return 1;
    }
    float value = std::atof((*valueString).c_str());
    if (print && value > 1000) {
        std::cout << "Error: too large a number\n";
        return 1;
    }
    if (invalid_value((*valueString), print))
        return 1;

    return 0;
}

int    BitcoinExchange::save_file(std::fstream &file) {
    std::string       line;
    std::string       date;
    std::string       valueString;
    long unsigned int counter = 0;

    getline(file, line);
    if (line != "date,exchange_rate")
        return 1;
    while (!file.eof()) {
        getline(file, line);
        if (line.empty())
            continue ;
        if (invalid_entry(line, &date, &valueString, ",",false))
            return 1;
        float value = std::atof(valueString.c_str());
        _map.insert(std::pair<std::string, float>(date, value));
        counter++;
    }
    if (_map.size() != counter || _map.size() == 0)
        return 1;    
    return 0;
}

void    BitcoinExchange::calculate_bitcoin(std::map<std::string, float>::iterator iterator, std::string date, std::string value) {
    float val = std::atof(value.c_str());
    float calc = iterator->second * val;
    std::cout << date << " => " << value << " = " << calc << "\n";    
}
