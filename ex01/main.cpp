/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:42 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/20 13:05:01 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RPN.hpp"

int main(int argc, char **argv) {
    std::stack<char>     stackElements;

    if (argc != 2){
        std::cout << "Error: invalid arguments\n";
        return 1;
    }
    try {
        validate_input(argv[1]);
        rpn(argv[1]);
    }
    catch (std::exception &e) {
        std::cout << e.what() << "\n";
    }
    return 0;
}