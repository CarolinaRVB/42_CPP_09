/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:24:33 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/09 17:00:06 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RPN.hpp"

int invalid_token(char c, std::string set) {
    int i = 0;

    while (set[i]) {
        if (set[i] == c)
            return (0);
        i++;
    }
    return (1);
}

int invalid_input(char *input, std::stack<int> *stackDigits, std::stack<char> *stackTokens) {
    std::string tokens = "+-/*";
    
    if (input[0] ==  '\0'){
        std::cout << "Error: empty input\n";
        return 1;
    }
    
    (void)stackDigits;
    (void)stackTokens;
    
    /* Check first 2 digits */
    if (!std::isdigit(input[0]) || !std::isdigit(input[2])) {
        std::cout << "Error\n";
        return 1;
    }
    
    /* Check Spaces between elements */
    for (int i = 0; input[i]; i++) {
        if (i%2 != 0 && input[i] != ' '){
            std::cout << "Error " << input[i] << "\n";
            return 1;
        }
    }
    
    int size = 0;
    for (int i = 0; input[i]; i++) {
        size++;
    }
    
    /* Last element needs to be token */
    if (invalid_token(input[--size], tokens)) {
            std::cout << "Error " << "\n";
            return 1;
    }

    /* Check Tokens positions */
    for (int i = 0; input[i] && i < size; i += 4) {
        if (i >= 4 && invalid_token(input[i], tokens)){
            std::cout << "Error " << input[i] << "\n";
            return 1;
        }
    }
    
    return 0;
}

void    rpn(char *input) {
    std::stack<int>     stackDigits;
    std::stack<char>    stackTokens;
      
    if (invalid_input(input, &stackDigits, &stackTokens))
        return ;
    
        
}