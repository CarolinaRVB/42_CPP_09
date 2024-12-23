/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:42 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/20 22:16:25 by crebelo-         ###   ########.fr       */
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
        if (validate_input(argv[1]))
            return 0;
        rpn(argv[1]);
    }
    catch (std::exception &e) {
        std::cout << e.what() << "\n";
    }
    return 0;
}