/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:24:33 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/26 11:16:23 by crebelo-         ###   ########.fr       */
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

void    perform_calculations(int *result, int left, int right, char oper) {
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
            break ;
        default:
            break;            
    }
}

int check_first_digits(char *input) {
    int found = 0;

    for (size_t i = 0; input[i]; i++) {
        if (found == 2)
            return 0;
        if (input[i] == ' ')
            continue;
        else if (isdigit(input[i]))
            found++;
        else {
            if (found != 2)
                return 1;
        }
    }
    return 0;
}

int one_digit(char *input) {
    int num = 0;
    int found = 0;

    for (size_t i = 0; input[i]; i++) {
        if (input[i] == ' ')
            continue;
        else if (isdigit(input[i])) {
            found++;
            num = input[i] - '0';
        }
        else 
            return 0;
    }
    if (found == 1)
        std::cout << num << "\n";
    else
        return 0;
    return 1;
}

void    validate_disposition(char *input, size_t *i, size_t size, size_t *counter) {
    if (*i + 1 < size && input[*i + 1] != ' ')
        throw  std::logic_error("Error: invalid arguments");
    (*i)++;
    (*counter)++;
    while (*i < size && isspace(input[*i]))
        (*i)++;
    (*i)--;  
}

int validate_input(char *input) {
    std::string tokens = "+-/*";
    size_t nums_counter = 0;
    size_t oper_counter = 0;
    size_t size = 0;
    
    get_size(input, &size);
    if (input[0] ==  '\0' || check_first_digits(input))
        throw std::logic_error("Error");
    if (one_digit(input))
        return 1;
    for (size_t i = 0; input[i]; i++) {
        if (isdigit(input[i]))
            validate_disposition(input, &i, size, &nums_counter);
        else if (valid_token((input[i]), tokens))
            validate_disposition(input, &i, size, &oper_counter);
        else if (input[i] == ' ')
            continue ;
        else
            throw  std::logic_error("Error: invalid arguments");
    }
    if (oper_counter != nums_counter - 1 || !oper_counter)
        throw  std::logic_error("Error: invalid arguments");   

    return 0;
}

void    rpn(char *nums) {
    int             left;
    int             right;  
    char            oper;
    int             result = 0;
    std::stack<int> stackElements;
    
    for (int i = 0; nums[i]; i++) {
        if (isdigit(nums[i]))
            stackElements.push(nums[i] - '0');
        else if (nums[i] != ' ') {
            oper = nums[i];
            right =  stackElements.top();
            stackElements.pop();
            if (stackElements.empty()) {
                left = right;
                if (!isdigit(nums[++i]))
                    throw std::logic_error("Error: invalid arguments");
                right = nums[i] - '0';
            }
            else {
                left = stackElements.top();
                stackElements.pop();
            }
            if (oper == '/' && right == 0)
                throw std::logic_error("Error: invalid arguments"); 
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

