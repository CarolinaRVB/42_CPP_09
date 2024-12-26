/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:24:31 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/26 11:15:43 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <algorithm>
# include <stack>

void     get_size(char *input, size_t *size);
int      valid_token(char c, std::string set);
void     validate_disposition(char *input, size_t *i, size_t size, size_t *counter);
int      validate_input(char *input);
void     rpn(char *input);

#endif