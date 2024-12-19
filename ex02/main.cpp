/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:37:35 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/19 16:27:13 by crebelo-         ###   ########.fr       */
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
        // std::cout << "Vec pair is: "<< (*m)[i][1] << "\n";   
    }
}

/*
    Initialize the sequence with the first pair and then the remaining big numbers (which are already sorted)
    The remaining b's go to pend
    
    The way Jacobsthal numbers dictate the order of insertion is like this: we start from the Jacobsthal number of 3. 
    We start insertion from element b3. We insert elements in the reverse order starting from this element, 
    until we hit b element of number of previous Jacobsthal number. In other words, the amount of inserted elements is
    In other words, the amount of inserted elements is current_jacobsthal - previous_jacobsthal.
    For the Jacobsthal number of 3, we insert 2 elements (3 - 1), b3, b2.
    For the Jacobsthal number of 5, we insert 2 elements (5 - 3), b5, b4.
    For the Jacobsthal number of 11, we insert 6 elements (11 - 5), b11, b10, b9, b8, b7, b6.
    I hope that you got the idea. And that you understand now that we can't always insert numbers this way.
    If there's not enough elemets to insert, for example, the Jacobsthal number is 11 (we should insert 6 elements),
    but we have only 3 elements in the pend, then we need to handle it somehow, and the simplest way to do this is 
    to insert the pend elements in order, as we did in recursion level 3.
*/
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
