/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:57:10 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/26 10:48:39 by crebelo-         ###   ########.fr       */
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

void    BitcoinExchange::handle_calculation(std::string *date, std::string *value) {
    std::map<std::string, float>::iterator iterator;
    
    iterator = _map.find(*date);
    if (iterator != _map.end())
        calculate_bitcoin(iterator, *date, *value);
    else {
        iterator = _map.lower_bound(*date);
        if (iterator != _map.begin())
            iterator--;
        if (iterator->first > *date)
            std::cout << "Error: bad input => " << *date << "\n";
        else
            calculate_bitcoin(iterator, *date, *value);
    }
}

void BitcoinExchange::handle_input(char *input) {
    std::fstream    file;
    std::string     line;
    std::string     date;
    std::string     value;
    bool first = true;

    file.open(input, std::fstream::in);
    if (file.fail())
        throw std::runtime_error("Error: failed to open input file");
    
    getline(file, line);
    while (!file.eof()) {
        if (first && line.substr(0, 12) == "date | value") {
            first = false;
            if (line.size() > 12) {
                file.close();
                throw std::logic_error("Error: invalid format");
            }
            else
                continue;
        }
        else if (first) 
            first = false;
        else
            getline(file, line);
        if (!line.empty()) {
            if (invalid_entry(line, &date, &value, "|", true))
                continue;
            else 
                handle_calculation(&date, &value);
        }
    }  
    file.close();
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

int check_set(char c, std::string set) {
    int i = 0;

    while (set[i]) {
        if (set[i] == c)
            return (0);
        i++;
    }
    return (1);
}

int error_return(bool print, std::string msg, std::string *date) {
    if (print && date)
        std::cout << msg << *date << "\n";
    else if (print)
        std::cout << msg;
    return 1;
}

/*
    A year is a leap year if:

    It is divisible by 4, AND
    It is not divisible by 100, UNLESS it is also divisible by 400.
*/
bool leap_year(int year) {
    return (year%4 == 0 && (year%100 != 0 || year%400 == 0));
}

bool    date_exists(int year, int month, int day, bool print) {
    if (year < 2009 || month < 1 || month > 12 || (!print && year > 2024 ))
        return false;

    int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (month == 2 && leap_year(year))
        month_days[1] = 29;
    
    if (day < 1 || day > month_days[month - 1])
        return false;
    return true;
}

int    invalid_date(std::string date, bool print) {
    std::string set = "0123456789-";
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi((date.substr(8, 2)).c_str());
    int i = 0;

    if (std::count(date.begin(), date.end(), '-')  != 2 || date.size() != 10
        || date[4] != '-' || date[7] != '-' )
        return (error_return(print, "Error: bad input => ", &date));

    while (date[i]) {
        if (check_set(date[i], set)) 
            return (error_return(print, "Error: bad input => ", &date));
        i++;
    }
    if (!date_exists(year, month, day, print)) 
        return (error_return(print, "Error: bad input => ", &date));

    return 0;
}

int    invalid_value(std::string value, bool print) {
    std::string doubles = "0123456789.";
    int i = 0;

    if (value[0] == '-')
        return (error_return(print, "Error: not a positive number.\n"));
    if (value[0] == '.' || (value[value.length() - 1] == '.') 
        || std::count(value.begin(), value.end(), '.') > 1)
            return (error_return(print, "Error: bad input => ", &value));
    while (value[i]) {
        if (check_set(value[i], doubles))
            return (error_return(print, "Error: bad input => ", &value));
        i++;
    }
    return 0;
}

int invalid_entry(std::string line, std::string *date, std::string *valueString, std::string sep, bool print) {
    std::size_t separator = line.find(sep);
    if (separator == std::string::npos)
        return (error_return(print, "Error: bad input => ", &line));

    if (print)
        separator--;
    *date = line.substr(0, separator);
    if (invalid_date(*date, print))
        return 1;
    size_t start = separator + 1;
    if (print)
        start += 2;
    if (start > line.size())
        return (error_return(print, "Error: bad input => ", date));
    
    *valueString = line.substr(start, line.size());
    if ((*valueString).empty())
        return (error_return(print, "Error: bad input => ", date));
    if (print) {
        if (line[start - 1] != ' ')
            return (error_return(print, "Error: bad input => ", date));
    }
    
    float value = std::atof((*valueString).c_str());
    if (print && value > 1000) 
        return (error_return(print, "Error: too large a number\n"));
    if (invalid_value((*valueString), print))
        return 1;

    return 0;
}
