/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:37:39 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/13 19:50:41 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <cstdlib>
# include <algorithm>
# include <limits>
# include <sys/time.h>
# include <iomanip>
# include <list>
# include <deque>

/*
What is Ford-Johnson with Jacobsthal?
The Ford-Johnson algorithm is about minimizing comparisons when sorting, using clever grouping and merging.

The Jacobsthal sequence guides:

How we split the elements into groups.
The order in which elements are inserted into the sorted subset.
*/

// VECTOR functions:
int     save_ints_deque(std::deque<std::deque<int> > *m, std::deque<int> *wrangler, char **arg, int argc);
bool    compareLargest_deque(std::deque<int> a, std::deque<int> b);
void    swap_largest_deque(std::deque<std::deque<int> > *intMatrix);
void    get_smallest_based_on_jacobsthall_deque(std::deque<std::deque<int> > *intMatrix, std::deque<int> *jacobsthal, std::deque<int> *sequence, std::deque<int> *pend);
void    create_jacobsthall_sequence_deque(unsigned long int size, std::deque<int> *jacobsthal);
void    insert_item_deque(std::deque<int> *vec, std::deque<int> *pend, int val, int i);
void    binary_insertion_deque(std::deque<int> *sequence, std::deque<int> *pend);

// DEQUE functions:
int     save_ints_vector(std::vector<std::vector<int> > *m, std::vector<int> *wrangler, char **arg, int argc);
bool    compareLargest_vector(std::vector<int> a, std::vector<int> b);
void    swap_largest_vector(std::vector<std::vector<int> > *intMatrix);
void    get_smallest_based_on_jacobsthall_vector(std::vector<std::vector<int> > *intMatrix, std::vector<int> *jacobsthal, std::vector<int> *sequence, std::vector<int> *pend);
void    create_jacobsthall_sequence_vector(unsigned long int size, std::vector<int> *jacobsthal);
void    insert_item_vector(std::vector<int> *vec, std::vector<int> *pend, int val, int i);
void    binary_insertion_vector(std::vector<int> *sequence, std::vector<int> *pend);


#endif