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

int invalid_input(char **arg) {
    for (int i = 1; arg[i]; i++) {
        for (int j = 0; arg[i][j]; j++) {
            if (!isdigit(arg[i][j]))
                return 1;
        }
    }
    return 0;
}

int    save_ints(std::vector<std::vector<int> > *m, std::vector<int> *wrangler, char **arg, int argc) {
    
    int size = argc;
    if (argc % 2 == 0)
        size = argc - 1;
        
    for (int i = 1; arg[i] && i < size; i += 2 ) {
        std::vector<int>    pair;
        float p1 = ::atof((arg[i]));
        float p2 = ::atof((arg[i + 1]));
        if (p1 > std::numeric_limits<int>::max() || p1 < std::numeric_limits<int>::min() ||
            p2 > std::numeric_limits<int>::max() || p2 < std::numeric_limits<int>::min())
            return 1;

        pair.push_back(static_cast<int>(p1));
        pair.push_back(static_cast<int>(p2));
        if (pair[0] > pair[1])
            std::swap(pair[0], pair[1]);
        (*m).push_back(pair);
    }

    if (size != argc) {
        float last = ::atof((arg[size]));
        if (last > std::numeric_limits<int>::max() || last < std::numeric_limits<int>::min())
            return 1;
        (*wrangler).push_back(static_cast<int>(last));
    }
    else
        (*wrangler).push_back(-1);
    
    return 0;    
}

void    print_matrix(std::vector<std::vector<int> > *m) {
    for (long unsigned int i = 0; i < (*m).size(); i++) {
        std::cout << "Next: \n";
        std::cout << "Vec pair is: "<< (*m)[i][0] << "\n";
        std::cout << "Vec pair is: "<< (*m)[i][1] << "\n";   
    }
}

bool    compareLargest(std::vector<int> a, std::vector<int> b) {
    return a[0] < b[0];
}

void    swap_largest(std::vector<std::vector<int> > *intMatrix) {
    std::sort(intMatrix->begin(), intMatrix->end(), compareLargest);
}

void    get_smallest_based_on_jacobsthall(std::vector<std::vector<int> > *intMatrix, std::vector<int> *jacobsthal, std::vector<int> *sequence, std::vector<int> *pend) {
    for (unsigned long int i = 0; i < jacobsthal->size(); i++) {      
        unsigned long int index = (*jacobsthal)[i];

        if (index < intMatrix->size() && std::find(jacobsthal->begin(), jacobsthal->begin() + i, index) == (jacobsthal->begin() + i)) {
            std::vector<int>::iterator iter;
            int val = (*intMatrix)[index][0];
            iter = std::lower_bound(sequence->begin(), sequence->end(), val);
            (*sequence).insert(iter, val);
            (*pend).push_back((*intMatrix)[index][1]);
        }
    }
    for (unsigned long int i = 0; i < intMatrix->size(); i++) {
        if (std::find(jacobsthal->begin(), jacobsthal->end(), i) == jacobsthal->end()) {
            (*pend).push_back((*intMatrix)[i][0]);
            (*pend).push_back((*intMatrix)[i][1]);
        }
    }
}

//8 3 7 1 4 6 5 2
/* Remove the extra 1 in beginning of sequence*/
void    create_jacobsthall_sequence(unsigned long int size, std::vector<int> *jacobsthal) {
    (*jacobsthal).push_back(0);
    (*jacobsthal).push_back(1);

    for (unsigned long int i = 2; i < size; i++) {
        int next = (*jacobsthal)[i - 1] + 2 * (*jacobsthal)[i - 2];
        (*jacobsthal).push_back(next);
    }
}

void    insert_item(std::vector<int> *vec, std::vector<int> *pend, int val, int i) {
    std::vector<int>::iterator  iter;

    if (val == -1)      
        val = (*pend)[i];
    iter = std::lower_bound(vec->begin(), vec->end(), val);
    
    vec->insert(iter, val);   
}



void    binary_insertion(std::vector<int> *sequence, std::vector<int> *pend) {
    for (unsigned long int i = 0; i < pend->size(); i++) {
        std::vector<int>::iterator iter;
        iter = std::lower_bound(sequence->begin(), sequence->end(), (*pend)[i]);
        sequence->insert(iter, (*pend)[i]);
    }
}

template <typename T>
void    print_vector(T nums, long unsigned int len, std::string message) {
    std::cout << message << " ";

    unsigned long int max = len;
    if (max > 5) {
        max = 5;
    }
    for (unsigned long int i = 0; i < max; i++) {
        std::cout << nums[i] << " ";
    }
    if (max != len)
        std::cout << "[...]";
    std::cout << "\n";
}

int main(int argc, char **argv) {
    std::vector<std::vector<int> >      intMatrix;
    std::vector<int>                    sequence;
    std::vector<int>                    pend;
    std::vector<int>                    jacobsthal;
    std::vector<int>                    wrangler;
    
    if (argc == 1) {
        std::cout << "Error: no argumentsn\n";
        return (1);
    }

    if (invalid_input(argv) || save_ints(&intMatrix, &wrangler, argv, argc)) {
        std::cout << "Error\n";
        return (1);
    }

    create_jacobsthall_sequence(intMatrix.size(), &jacobsthal);
    get_smallest_based_on_jacobsthall(&intMatrix, &jacobsthal, &sequence, &pend);
    binary_insertion(&sequence, &pend);
    

    if (wrangler[0] != -1)
        insert_item(&sequence, &wrangler, -1, 0);


    argv++;
    print_vector<char **>(argv, argc, "Before:");
    print_vector<std::vector<int> >(sequence, sequence.size(), "After: ");
}

/*
7116 17049 80332 56293 59359 29829 76080 46809 41283 80805 26309 75680 34277 85291 80174 28348 36599
0       0   7116 17049 26309 28348 29829 34277 36599 59359 75680 76080 80174 80174 80332 80805 85291
7116 17049 26309 28348 29829 34277 41283 46809 56293 59359 75680 76080 80174 80332 80805 85291
7116 17049 26309 28348 29829 34277 36599 41283 46809 56293 59359 75680 76080 80174 80332 80805 85291
56293
46809
41283
*/