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

int invalid_input(char *input, std::stack<char> *stackElements) {
    std::string tokens = "+-/*";
    
    if (input[0] ==  '\0'){
        std::cout << "Error: empty input\n";
        return 1;
    }
    
    
    /* Check first 2 digits */
    if (!std::isdigit(input[0]) || !std::isdigit(input[2])) {
        std::cout << "Error\n";
        return 1;
    }
    
    /* Check Spaces between elements */
    for (int i = 0; input[i]; i++) {
        if ((i%2 != 0 && input[i] != ' ')
            || (input[i] != ' ' && invalid_token(input[i], tokens) && !isdigit(input[i]))){
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

    /* Check if valid tokens */
    for (int i = 0; input[i]; i++) {
        if (!isdigit(input[i]) && input[i] != ' ' && invalid_token(input[i], tokens)) {
            std::cout << "Error\n";
            return 1;
        }
    }

    for (int i = size--; input[i]; i--) {
        if (input[i] != ' ')
            (*stackElements).push(input[i]);
    }

    // while (!(*stackElements).empty()) {
    //     std::cout << "Element = " << (*stackElements).top() << "\n";
    //     (*stackElements).pop();
    // }
    return 0;
}

/*
    $> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
    42
    $> ./RPN "7 7 * 7 -"
    42
    $> ./RPN "1 2 * 2 / 2 * 2 4 - +"
    0
    $> ./RPN "(1 + 1)"
    Error

*/

void    perform_calculations(size_t *result, size_t left, size_t right, char oper) {
    switch (oper) {
        case '*':
            *result = left * right;
            std::cout << *result << "\n";
            break;
        // default:
            
    }


}

void    rpn(char *input) {
    std::stack<char>     stackElements;
    size_t  left;
    size_t  right;  
    char  oper;

    size_t result;

    if (invalid_input(input, &stackElements))
        return ;

    left = stackElements.top();
    stackElements.pop();
    right = stackElements.top();
    stackElements.pop();
    oper = stackElements.top();
    stackElements.pop();
    perform_calculations(&result, left, right, oper);
    while (!stackElements.empty()) {
        if (isdigit(stackElements.top())) {
            right = stackElements.top();
            stackElements.pop();

            if (isdigit(stackElements.top())) {
                left = right;
                right = stackElements.top();
                stackElements.pop();
            }
            else 
                left = result;
        }
        if (invalid_token(stackElements.top(), "+-/*")) {
            std::cout << "Error\n";
        }
        oper = stackElements.top();
        stackElements.pop();
        
        perform_calculations(&result, left, right, oper);
    }
    
    std::cout << result << "\n";
}