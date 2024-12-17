/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:37:35 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/17 16:42:24 by crebelo-         ###   ########.fr       */
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

    // unsigned long int max = len;
    // if (max > 5) {
    //     max = 5;
    // }
    for (unsigned long int i = 0; i < len; i++) {
        std::cout << nums[i] << " ";
    }
    // if (max != len)
    //     std::cout << "[...]";
    std::cout << std::endl;
}

void    print_result(int argc, char **argv, std::vector<int> *sequence, double timeVec, double timeD) {
    print_nums(++argv, argc - 1, "Before:");
    print_nums(*sequence, sequence->size(), "After: ");
    std::cout << "Time to process a range of 5 elements with std::vector : " << std::fixed << std::setprecision(5) << timeVec << " us \n";
    std::cout << "Time to process a range of 5 elements with std::deque : " << std::fixed << std::setprecision(5) << timeD << " us \n";    
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

    create_jacobsthall_sequence_vector(intMatrix.size(), &jacobsthal);
    get_smallest_based_on_jacobsthall_vector(&intMatrix, &jacobsthal, sequence, &pend);
    binary_insertion_vector(sequence, &pend);
    
    if (wrangler[0] != -1)
        insert_item_vector(sequence, &wrangler, -1, 0);

    return 0;
}

int    sort_deque(int argc, char **argv, std::deque<int> *sequenceD) {
    std::deque<std::deque<int> >       intMatrixD;
    std::deque<int>                    pendD;
    std::deque<int>                    jacobsthalD;
    std::deque<int>                    wranglerD;

    if (invalid_input(argv) || save_ints_deque(&intMatrixD, &wranglerD, argv, argc)) {
        std::cout << "Error\n";
        return (1);
    }

    create_jacobsthall_sequence_deque(intMatrixD.size(), &jacobsthalD);
    get_smallest_based_on_jacobsthall_deque(&intMatrixD, &jacobsthalD, sequenceD, &pendD);
    binary_insertion_deque(sequenceD, &pendD);
    
    if (wranglerD[0] != -1)
        insert_item_deque(sequenceD, &wranglerD, -1, 0);
    
    return 0;
}

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
