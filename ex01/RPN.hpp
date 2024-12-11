/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:24:31 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/09 16:12:40 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <algorithm>
# include <stack>

void     get_size(char *input, int *size);
int      invalid_token(char c, std::string set);
void     get_first_calculation(std::stack<char> *stackElements, size_t *right, size_t *left, char *oper);
int      invalid_internal_calculations(std::stack<char> *stackElements, size_t *right, size_t left, char oper);
int      validate_input(char *input, std::stack<char> *stackElements);
void     rpn(std::stack<char> stackElements);

#endif