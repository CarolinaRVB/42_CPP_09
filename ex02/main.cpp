/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:37:35 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/20 14:30:06 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "PmergeMe.hpp"

int invalid_input(char **arg) {
    for (int i = 1; arg[i]; i++) {
        for (int j = 0; arg[i][j]; j++) {
            if (!isdigit(arg[i][j]))
                return 1;
        }
    }
    return 0;
}

template <typename T>
void    print_nums(T nums, long unsigned int len, std::string message) {
    std::cout << message << " ";

    for (unsigned long int i = 0; i < len; i++) {
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;
}

void    print_result(int argc, char **argv, std::vector<int> *sequence, double timeVec, double timeD) {
    print_nums(++argv, argc - 1, "Before:");
    print_nums(*sequence, sequence->size(), "After: ");
    std::cout << "Time to process a range of 5 elements with std::vector : " << std::fixed << std::setprecision(5) << timeVec << " us \n";
    std::cout << "Time to process a range of 5 elements with std::deque : " << std::fixed << std::setprecision(5) << timeD << " us \n";    
}

void    print_matrix(std::vector<std::vector<int> > *m) {
    std::cout << "PAIRS:: \n";
    for (long unsigned int i = 0; i < (*m).size(); i++) {
        std::cout << "Vec pair is: "<< (*m)[i][0] << ", " << (*m)[i][1] << "\n";
    }
}

int    sort_vector(int argc, char **argv, std::vector<int> *sequence) {
    std::vector<std::vector<int> >      intMatrix;
    std::vector<int>                    pend;
    std::vector<int>                    jacobsthal;
    std::vector<int>                    wrangler;


    if (invalid_input(argv) || save_ints_vector(&intMatrix, &wrangler, argv, argc)) {
        std::cout << "Error\n";
        return (1);
    }
    merge_insert_vector(&intMatrix);
    jacobsthal_insert_vector(&intMatrix, &jacobsthal, sequence, &pend);
    if (wrangler[0] != -1)
        insert_item_vector(sequence, &wrangler, -1, 0);

    return 0;
}

int    sort_deque(int argc, char **argv, std::deque<int> *sequence) {
    std::deque<std::deque<int> >       intMatrix;
    std::deque<int>                    pend;
    std::deque<int>                    jacobsthal;
    std::deque<int>                    wrangler;

    if (invalid_input(argv) || save_ints_deque(&intMatrix, &wrangler, argv, argc)) {
        std::cout << "Error\n";
        return (1);
    }
    merge_insert_deque(&intMatrix);
    jacobsthal_insert_deque(&intMatrix, &jacobsthal, sequence, &pend);
    
    if (wrangler[0] != -1)
        insert_item_deque(sequence, &wrangler, -1, 0);
    
    return 0;
}


/*
    big num set --> vector is faster
    small num set --> deque is faster
    why?
        - Vector stores elements in a continuous block of memory -> fast access
        - Deque is implemented as a series of smaller continuous blocks of memory - slower
*/
int main(int argc, char **argv) {

    if (argc == 1) {
        std::cout << "Error: no arguments\n";
        return (1);
    }
    
    // Sorting Nums with a VECTOR container
    std::vector<int>                    sequence;
    clock_t startVec = clock();
    if (sort_vector(argc, argv, &sequence) != 0)
        return 1;
    clock_t endVec = clock();
    double timeVec = static_cast<double>(endVec - startVec) / 1000; 

    // Sorting Nums with a DEQUE container
    std::deque<int>                    sequenceD;
    clock_t startD = clock();   
    if (sort_deque(argc, argv, &sequenceD) != 0)
        return 1;    
    clock_t endD = clock();
    double timeD = static_cast<double>(endD - startD) / 1000; 

    // Show final results
    print_result(argc, argv, &sequence, timeVec, timeD);

    return 0;    
}
