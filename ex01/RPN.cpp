/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:24:33 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/10 18:11:23 by crebelo-         ###   ########.fr       */
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

void get_size(char *input, int *size) {
    for (int i = 0; input[i]; i++) {
        (*size)++;
    }
}

void    perform_calculations(size_t *result, size_t left, size_t right, char oper) {
    switch (oper) {
        case '*':
            *result = left * right;
            break;
        case '-':
            *result = left - right;
            break;
        case '+':
            *result = left + right;
            break;
        case '/':
            *result = left / right;
        default:
            break;            
    }
}

int invalid_internal_calculations(std::stack<char> *stackElements, size_t *right, size_t left, char oper) {
    size_t tmp;
    
    left = *right;
    *right = static_cast<size_t>((*stackElements).top() - '0');
    (*stackElements).pop();
    if (invalid_token((*stackElements).top(), "+-/*"))
        return 1;
    oper = (*stackElements).top();
    (*stackElements).pop();
    perform_calculations(&tmp, left, *right, oper);
    *right = tmp;
    return 0;
};

void    get_first_calculation(std::stack<char> *stackElements, size_t *right, size_t *left, char *oper) {
    *left = static_cast<size_t>((*stackElements).top() - '0');
    (*stackElements).pop();
    *right = static_cast<size_t>((*stackElements).top() - '0');
    (*stackElements).pop();
    *oper = (*stackElements).top();
    (*stackElements).pop();
}

int validate_input(char *input, std::stack<char> *stackElements) {
    std::string tokens = "+-/*";
    int size = 0;
    
    get_size(input, &size);
    if (input[0] ==  '\0' || !std::isdigit(input[0]) || !std::isdigit(input[2]) || invalid_token(input[--size], tokens))
        throw std::logic_error("Error");

    for (int i = 0; input[i]; i++) {
        if ((i%2 != 0 && input[i] != ' ')
            || (input[i] != ' ' && invalid_token(input[i], tokens) && !isdigit(input[i])))
            throw std::logic_error("Error");
    }

    for (int i = size--; input[i]; i--) {
        if (input[i] != ' ')
            (*stackElements).push(input[i]);
    }
    return 0;
}

void    rpn(std::stack<char> stackElements) {
    size_t  left;
    size_t  right;  
    size_t  result;
    char    oper;

    get_first_calculation(&stackElements, &right, &left, &oper);
    perform_calculations(&result, left, right, oper);
    while (!stackElements.empty()) {
        if (isdigit(stackElements.top())) {
            right = static_cast<size_t>(stackElements.top() - '0');
            stackElements.pop();

            if (isdigit(stackElements.top()) && invalid_internal_calculations(&stackElements, &right, left, oper))
                throw std::logic_error("Error");
            left = result;
            if (invalid_token(stackElements.top(), "+-/*"))
                throw std::logic_error("Error");
            oper = stackElements.top();
            stackElements.pop(); 
            perform_calculations(&result, left, right, oper);
        }
        else 
            throw std::logic_error("Error");
    }
    std::cout << result << "\n";
}


// void    rpn(char *input) {
//     std::stack<char>     stackElements;
//     size_t  left;
//     size_t  right;  
//     size_t result;
//     char  oper;

//     if (invalid_input(input, &stackElements))
//         return ;
//     get_first_calculation(&stackElements, &right, &left, &oper);
//     perform_calculations(&result, left, right, oper);
//     while (!stackElements.empty()) {
//         if (isdigit(stackElements.top())) {
//             right = static_cast<size_t>(stackElements.top() - '0');
//             stackElements.pop();

//             if (isdigit(stackElements.top())) {
//                 if (invalid_internal_calculations(&stackElements, &right, left, oper))
//                     return ;
//             }
//             left = result;
//         }
//         else {
//             std::cout << "Error\n";
//             return;
//         }
//         if (invalid_token(stackElements.top(), "+-/*")) {
//             std::cout << "Error\n";
//             return;
//         }
//         oper = stackElements.top();
//         stackElements.pop(); 
//         perform_calculations(&result, left, right, oper);
//     }
//     std::cout << result << "\n";
// }