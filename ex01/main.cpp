/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:42 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/09 16:12:30 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RPN.hpp"

int main(int argc, char **argv) {
    std::stack<char>     stackElements;
    
    if (argc == 1){
        std::cout << "Error: no arguments provided\n";
        return 1;
    }

    try {
        validate_input(argv[1], &stackElements);
        rpn(stackElements);
    }
    catch (std::exception &e) {
        std::cout << e.what() << "\n";
    }
    return 0;
}