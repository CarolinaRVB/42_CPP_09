/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:37:35 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/12 11:42:50 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "PmergeMe.hpp"

/* Check if ints are valid */
int invalid_input(char **arg) {
    for (int i = 1; arg[i]; i++) {
        for (int j = 0; arg[i][j]; j++) {
            if (!isdigit(arg[i][j]))
                return 1;
        }
    }
    return 0;
}

void    save_ints(std::vector<std::vector<int> > *m, std::vector<int> *wrangler, char **arg, int argc) {
    
    int size = argc;
    if (argc % 2 == 0)
        size = argc - 1;
        
    for (int i = 1; arg[i] && i < size; i += 2 ) {
        std::vector<int>    pair;
        
        pair.push_back(::atoi((arg[i])));
        pair.push_back(::atoi((arg[i + 1])));
        if (pair[0] > pair[1])
            std::swap(pair[0], pair[1]);
        (*m).push_back(pair);
    }

    if (size != argc) 
        (*wrangler).push_back(::atoi(arg[size]));
    else
        (*wrangler).push_back(-1);
    
    // if (size != argc) {
    //     std::vector<int>    pair;
    //     pair.push_back(::atoi((arg[size])));
    //     pair.push_back(-1);
    //     (*m).push_back(pair);
    // }        
}

void    print_matrix(std::vector<std::vector<int> > *m) {
    for (long unsigned int i = 0; i < (*m).size(); i++) {
        std::cout << "Next: \n";
        std::cout << "Vec pair is: "<< (*m)[i][0] << "\n";
        std::cout << "Vec pair is: "<< (*m)[i][1] << "\n";   
    }
}


/*
    4. Sort the sequence recursively by the value of its largest pair.
    Purpose: Establish order among the largest elements of the pairs (which dominate the overall sort).
    How:
    Consider the second element of each pair (greater) as the key for recursive sorting.
    Sort the pairs based on these keys.
    Example: For [(3, 8), (5, 7)], the keys are [8, 7]. Sorting by these gives [(5, 7), (3, 8)].
    Why: Sorting by the largest values ensures that the overall structure of the array converges toward order.
*/
void    recursive_largest(std::vector<std::vector<int> > *intMatrix) {
    
    for (unsigned long int i = 0; i < intMatrix->size() - 1; i++) {
        for (unsigned long int j = i + 1; j < intMatrix->size(); j++) {
            if (intMatrix[i][1] > intMatrix[j][1]) {
                std::swap(intMatrix[i], intMatrix[j]);
            }
        }   
    }
}

int main(int argc, char **argv) {
    std::vector<std::vector<int> >   intMatrix;
    std::vector<int>   wrangler;
    
    if (argc == 1) {
        std::cout << "Error: no argumentsn\n";
        return (1);
    }

    if (invalid_input(argv)) {
        std::cout << "Error\n";
        return (1);
    }
    save_ints(&intMatrix, &wrangler, argv, argc);
    // print_matrix(&intMatrix);
    recursive_largest(&intMatrix);
    print_matrix(&intMatrix);

}