/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:37:42 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/18 14:41:57 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*
#########################    USING DEQUE CONTAINER    #########################
*/
int    save_ints_deque(std::deque<std::deque<int> > *m, std::deque<int> *wrangler, char **arg, int argc) {
    
    int size = argc;
    if (argc % 2 == 0)
        size = argc - 1;
        
    for (int i = 1; arg[i] && i < size; i += 2 ) {
        std::deque<int>    pair;
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

bool    compareLargest_deque(std::deque<int> a, std::deque<int> b) {
    return a[0] < b[0];
}

void    swap_largest_deque(std::deque<std::deque<int> > *intMatrix) {
    std::sort(intMatrix->begin(), intMatrix->end(), compareLargest_deque);
}

void    get_smallest_based_on_jacobsthall_deque(std::deque<std::deque<int> > *intMatrix, std::deque<int> *jacobsthal, std::deque<int> *sequence, std::deque<int> *pend) {
    for (unsigned long int i = 0; i < jacobsthal->size(); i++) {      
        unsigned long int index = (*jacobsthal)[i];

        if (index < intMatrix->size() && std::find(jacobsthal->begin(), jacobsthal->begin() + i, index) == (jacobsthal->begin() + i)) {
            std::deque<int>::iterator iter;
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

void    create_jacobsthall_sequence_deque(unsigned long int size, std::deque<int> *jacobsthal) {
    (*jacobsthal).push_back(0);
    (*jacobsthal).push_back(1);

    for (unsigned long int i = 2; i < size; i++) {
        int next = (*jacobsthal)[i - 1] + 2 * (*jacobsthal)[i - 2];
        (*jacobsthal).push_back(next);
    }
}

void    insert_item_deque(std::deque<int> *vec, std::deque<int> *pend, int val, int i) {
    std::deque<int>::iterator  iter;

    if (val == -1)      
        val = (*pend)[i];
    iter = std::lower_bound(vec->begin(), vec->end(), val);
    
    vec->insert(iter, val);   
}

void    binary_insertion_deque(std::deque<int> *sequence, std::deque<int> *pend) {
    for (unsigned long int i = 0; i < pend->size(); i++) {
        std::deque<int>::iterator iter;
        iter = std::lower_bound(sequence->begin(), sequence->end(), (*pend)[i]);
        sequence->insert(iter, (*pend)[i]);
    }
}

/*
#########################    USING VECTOR CONTAINER    #########################
*/
int    save_ints_vector(std::vector<std::vector<int> > *m, std::vector<int> *wrangler, char **arg, int argc) {
    
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

void    print_matrix_vector(std::vector<std::vector<int> > *m) {
    for (long unsigned int i = 0; i < (*m).size(); i++) {
        std::cout << "Next: \n";
        std::cout << "Vec pair is: "<< (*m)[i][0] << "\n";
        std::cout << "Vec pair is: "<< (*m)[i][1] << "\n";   
    }
}

bool    compareLargest_vector(std::vector<int> a, std::vector<int> b) {
    return a[0] < b[0];
}

void    swap_largest_vector(std::vector<std::vector<int> > *intMatrix) {
    std::sort(intMatrix->begin(), intMatrix->end(), compareLargest_vector);
}

/*
    Here we go through the jacobsthal sequence
    We get the current index on the jacobsthal
    Then we check if that index is in the bounds of the main vector container and if it's not a repeated index like in the case of the '1'
        Then we go to that index on our main vector container and we get the smallest value (not yet sorted)
        We find the lower_bound on our sequence vector - here it's empty in the beginning ?? and we insert the smaller values
        THen the bigger values are directly inserted on the pend ???
        
        Then the remaining elements on the vector that weren't appended are added to the end of the pend vector 
        here a simple check is done to skip the indexes that correspond to the jacobstal
*/
void    get_smallest_based_on_jacobsthall_vector(std::vector<std::vector<int> > *intMatrix, std::vector<int> *jacobsthal, std::vector<int> *sequence, std::vector<int> *pend) {
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

void    create_jacobsthall_sequence_vector(unsigned long int size, std::vector<int> *jacobsthal) {
    (*jacobsthal).push_back(0);
    (*jacobsthal).push_back(1);

    for (unsigned long int i = 2; i < size; i++) {
        int next = (*jacobsthal)[i - 1] + 2 * (*jacobsthal)[i - 2];
        (*jacobsthal).push_back(next);
    }
}

void    insert_item_vector(std::vector<int> *vec, std::vector<int> *pend, int val, int i) {
    std::vector<int>::iterator  iter;

    if (val == -1)      
        val = (*pend)[i];
    iter = std::lower_bound(vec->begin(), vec->end(), val);
    
    vec->insert(iter, val);   
}

void    binary_insertion_vector(std::vector<int> *sequence, std::vector<int> *pend) {
    for (unsigned long int i = 0; i < pend->size(); i++) {
        std::vector<int>::iterator iter;
        iter = std::lower_bound(sequence->begin(), sequence->end(), (*pend)[i]);
        sequence->insert(iter, (*pend)[i]);
    }
}
 