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
# include <fstream>
# include <stack>
 /*
    Tokens: + - / *

    $> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"

    The functions associated with stack are: 
    empty() – Returns whether the stack is empty – Time Complexity : O(1) 
    size() – Returns the size of the stack – Time Complexity : O(1) 
    top() – Returns a reference to the top most element of the stack – Time Complexity : O(1) 
    push(g) – Adds the element ‘g’ at the top of the stack – Time Complexity : O(1) 
    pop() – Deletes the most recent entered element of the stack – Time Complexity : O(1) 


    can have 2 stacks -> one for ints and one for string 
 */

void    rpn(char *input);
int     invalid_input(char *input);


#endif