/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:37:42 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/26 11:39:13 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*
#########################    USING DEQUE CONTAINER    #########################
*/

int duplicates_deque(std::deque<std::deque<int> > *m, int p1, int p2 = 0) {
    int count_p1 = 0;
    int count_p2 = 0;
    for (size_t j = 0; j < m->size(); j++) {
        count_p1 += std::count((*m)[j].begin(), (*m)[j].end(), p1);
        if (p2)
            count_p2 += std::count((*m)[j].begin(), (*m)[j].end(), p2);
    }
    if ((!p2 && p1 >= 1) || count_p1 > 1 || count_p2 > 1)
        return 1;
    return 0;
}

int    save_ints_deque(std::deque<std::deque<int> > *m, std::deque<int> *wrangler, char **arg, int argc) {
    
    int size = argc;
    if (argc % 2 == 0)
        size = argc - 1;
        
    for (int i = 1; arg[i] && i < size; i += 2 ) {
        std::deque<int>    pair;
        float p1 = ::atof((arg[i]));
        float p2 = ::atof((arg[i + 1]));
        if (p1 > std::numeric_limits<int>::max() || p1 == 0 ||
            p2 > std::numeric_limits<int>::max() || p2 == 0 )
            return 1;

        pair.push_back(static_cast<int>(p1));
        pair.push_back(static_cast<int>(p2));
        if (pair[0] > pair[1])
            std::swap(pair[0], pair[1]);
        (*m).push_back(pair);

        if (duplicates_deque(m, pair[0], pair[1]))
            return 1;
    }

    if (size != argc) {
        float last = ::atof((arg[size]));
        if (last > std::numeric_limits<int>::max() || last < std::numeric_limits<int>::min())
            return 1;
        (*wrangler).push_back(static_cast<int>(last));
    }
    else
        (*wrangler).push_back(-1);

    if (duplicates_deque(m, (*wrangler)[0]))
            return 1;
    return 0;    
}

void    merge_insert_deque(std::deque<std::deque<int> > *intMatrix, size_t start) {
    
    if (start >= intMatrix->size() - 1)
        return ;

    for (unsigned long int j = start + 1; j < intMatrix->size(); j++) {
        if ((*intMatrix)[start][1] > (*intMatrix)[j][1])
            std::swap((*intMatrix)[start], (*intMatrix)[j]);
    }
    merge_insert_deque(intMatrix, start + 1);
}

void    create_jacobsthall_sequence_deque(unsigned long int size, std::deque<int> *jacobsthal) {
    (*jacobsthal).push_back(1);
    (*jacobsthal).push_back(3);

    for (unsigned long int i = 2; i < size; i++) {
        int next = (*jacobsthal)[i - 1] + 2 * (*jacobsthal)[i - 2];
        (*jacobsthal).push_back(next);
    }
}

void    jacobsthal_insert_deque(std::deque<std::deque<int> > *intMatrix, std::deque<int> *jacobsthal, std::deque<int> *sequence, std::deque<int> *pend) {
    
    create_jacobsthall_sequence_deque(intMatrix->size(), jacobsthal);
    
    // Starting sequence with first pair
    (*sequence).push_back((*intMatrix)[0][0]);
    (*sequence).push_back((*intMatrix)[0][1]);

    for (size_t i = 1; i < intMatrix->size(); i++) {
        (*pend).push_back((*intMatrix)[i][0]);
        (*sequence).push_back((*intMatrix)[i][1]);
    }
    
    for (size_t i = 1; i < jacobsthal->size(); i++) {
        size_t total = std::min((*jacobsthal)[i] - (*jacobsthal)[i - 1], static_cast<int>(pend->size()));       
        size_t start = std::min(static_cast<int>(pend->size()) - 1, (*jacobsthal)[i]);

        while (total) {
            std::deque<int>::iterator iter;
            iter = std::lower_bound(sequence->begin(), sequence->end(), (*pend)[start]);
            (*sequence).insert(iter, (*pend)[start]);
            (*pend).erase(pend->begin() + start);
            start--;
            total--;
        }
        if (pend->empty())
            break ;
    }
}

void    insert_item_deque(std::deque<int> *vec, std::deque<int> *pend, int val, int i) {
    std::deque<int>::iterator  iter;

    if (val == -1)      
        val = (*pend)[i];
    iter = std::lower_bound(vec->begin(), vec->end(), val);
    
    vec->insert(iter, val);   
}


/*
#########################    USING VECTOR CONTAINER    #########################
*/

int duplicates_vector(std::vector<std::vector<int> > *m, int p1, int p2 = 0) {
    int count_p1 = 0;
    int count_p2 = 0;
    for (size_t j = 0; j < m->size(); j++) {
        count_p1 += std::count((*m)[j].begin(), (*m)[j].end(), p1);
        if (p2)
            count_p2 += std::count((*m)[j].begin(), (*m)[j].end(), p2);
    }
    if ((!p2 && p1 >= 1) || count_p1 > 1 || count_p2 > 1)
        return 1;
    return 0;
}

int    save_ints_vector(std::vector<std::vector<int> > *m, std::vector<int> *wrangler, char **arg, int argc) {
    
    int size = argc;
    if (argc % 2 == 0)
        size = argc - 1;
        
    for (int i = 1; arg[i] && i < size; i += 2 ) {
        std::vector<int>    pair;
        float p1 = ::atof((arg[i]));
        float p2 = ::atof((arg[i + 1]));
        if (p1 > std::numeric_limits<int>::max() || p1 == 0 ||
            p2 > std::numeric_limits<int>::max() || p2 == 0)
            return 1;

        pair.push_back(static_cast<int>(p1));
        pair.push_back(static_cast<int>(p2));
        if (pair[0] > pair[1])
            std::swap(pair[0], pair[1]);
        (*m).push_back(pair);

        if (duplicates_vector(m, pair[0], pair[1]))
            return 1;
    }

    if (size != argc) {
        float last = ::atof((arg[size]));
        if (last > std::numeric_limits<int>::max() || last < std::numeric_limits<int>::min())
            return 1;
        (*wrangler).push_back(static_cast<int>(last));
    }
    else
        (*wrangler).push_back(-1);
    if (duplicates_vector(m, (*wrangler)[0]))
        return 1;
    return 0;    
}

void    print_matrix_vector(std::vector<std::vector<int> > *m) {
    for (long unsigned int i = 0; i < (*m).size(); i++) {
        std::cout << "Next: \n";
        std::cout << "Vec pair is: "<< (*m)[i][0] << "\n";
        std::cout << "Vec pair is: "<< (*m)[i][1] << "\n";   
    }
}

void    merge_insert_vector(std::vector<std::vector<int> > *intMatrix, size_t start) {
    
    if (start >= intMatrix->size() - 1)
        return ;

    for (unsigned long int j = start + 1; j < intMatrix->size(); j++) {
        if ((*intMatrix)[start][1] > (*intMatrix)[j][1])
            std::swap((*intMatrix)[start], (*intMatrix)[j]);
    }
    merge_insert_vector(intMatrix, start + 1);
}

void    create_jacobsthall_sequence_vector(unsigned long int size, std::vector<int> *jacobsthal) {
    (*jacobsthal).push_back(1);
    (*jacobsthal).push_back(3);

    for (unsigned long int i = 2; i < size; i++) {
        int next = (*jacobsthal)[i - 1] + 2 * (*jacobsthal)[i - 2];
        (*jacobsthal).push_back(next);
    }
}

void    jacobsthal_insert_vector(std::vector<std::vector<int> > *intMatrix, std::vector<int> *jacobsthal, std::vector<int> *sequence, std::vector<int> *pend) {
    
    create_jacobsthall_sequence_vector(intMatrix->size(), jacobsthal);
    
    // Starting sequence with first pair
    (*sequence).push_back((*intMatrix)[0][0]);
    (*sequence).push_back((*intMatrix)[0][1]);

    for (size_t i = 1; i < intMatrix->size(); i++) {
        (*pend).push_back((*intMatrix)[i][0]);
        (*sequence).push_back((*intMatrix)[i][1]);
    }
    
    for (size_t i = 1; i < jacobsthal->size(); i++) {
        size_t total = std::min((*jacobsthal)[i] - (*jacobsthal)[i - 1], static_cast<int>(pend->size()));       
        size_t start = std::min(static_cast<int>(pend->size()) - 1, (*jacobsthal)[i]);

        while (total) {
            std::vector<int>::iterator iter;
            iter = std::lower_bound(sequence->begin(), sequence->end(), (*pend)[start]);
            (*sequence).insert(iter, (*pend)[start]);
            (*pend).erase(pend->begin() + start);
            start--;
            total--;
        }
        if (pend->empty())
            break ;
    }
}

void    insert_item_vector(std::vector<int> *vec, std::vector<int> *pend, int val, int i) {
    std::vector<int>::iterator  iter;

    if (val == -1)      
        val = (*pend)[i];
    iter = std::lower_bound(vec->begin(), vec->end(), val);
    
    vec->insert(iter, val);   
}

 