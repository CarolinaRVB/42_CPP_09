/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:24:33 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/19 19:05:51 by crebelo-         ###   ########.fr       */
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

int validate_input(char *input) {
    std::string tokens = "+-/*";
    int size = 0;
    
    get_size(input, &size);
    if (input[0] ==  '\0' || !std::isdigit(input[0]) || !std::isdigit(input[2]) || invalid_token(input[--size], tokens))
        throw std::logic_error("Error");
    
    
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
            throw std::logic_error("Error in rpn");
    }
    std::cout << result << "\n";
}

