/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:24:33 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/20 08:47:42 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RPN.hpp"

int valid_token(char c, std::string set) {
    int i = 0;

    while (set[i]) {
        if (set[i] == c)
            return (1);
        i++;
    }
    return (0);
}

void get_size(char *input, size_t *size) {
    for (size_t i = 0; input[i]; i++) {
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

int validate_input(char *input) {
    std::string tokens = "+-/*";
    size_t nums_counter = 0;
    size_t oper_counter = 0;
    size_t size = 0;
    
    get_size(input, &size);
    if (input[0] ==  '\0' || !std::isdigit(input[0]) || !std::isdigit(input[2]))
        throw std::logic_error("Error");
    
    for (size_t i = 0; input[i]; i++) {
        if (isdigit(input[i])) {
            if (i + 1 < size && input[i + 1] != ' ')
                throw  std::logic_error("Error1: invalid arguments");
            i++;
            nums_counter++;
            while (i < size && isspace(input[i]))
                i++;
            i--;
        }
        else if (valid_token((input[i]), tokens)) {
            if (i + 1 < size && input[i + 1] != ' ')
                throw  std::logic_error("Error2: invalid arguments");
            i++;
            oper_counter++;
            while (i < size && isspace(input[i]))
                i++;
            i--;   
        }
        else
            throw  std::logic_error("Error3: invalid arguments");
    }
    if (oper_counter != nums_counter - 1)
        throw  std::logic_error("Error4: invalid arguments");   

    return 0;
}


void    rpn(char *nums) {
    size_t  left;
    size_t  right;  
    size_t  result;
    char    oper;
    std::stack<size_t> stackElements;
    
    result = 0;
    for (size_t i = 0; nums[i]; i++) {
        if (isdigit(nums[i])){
            stackElements.push(nums[i] - '0');
        }
        else if (nums[i] != ' ') {
            oper = nums[i];
            right =  static_cast<size_t>(stackElements.top());
            stackElements.pop();
            if (stackElements.empty()) {
                left = right;
                right = static_cast<size_t>(nums[++i] - '0');
            }
            else
                left =  static_cast<size_t>(stackElements.top());
            stackElements.pop();
            perform_calculations(&result, left, right, oper);
            stackElements.push(result);
        }
        else if (nums[i] == ' ')
            continue ;
        else
            throw std::logic_error("Error: invalid arguments");
    }
    std::cout << result << "\n";
}

