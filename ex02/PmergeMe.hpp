/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:37:39 by crebelo-          #+#    #+#             */
/*   Updated: 2024/12/19 16:22:19 by crebelo-         ###   ########.fr       */
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
# include <ctime>


/*
What is Ford-Johnson with Jacobsthal?
The Ford-Johnson algorithm is about minimizing comparisons when sorting, using clever grouping and merging.

The Jacobsthal sequence guides:

How we split the elements into groups.
The order in which elements are inserted into the sorted subset.
*/

// DEQUE functions:
int     duplicates_deque(std::deque<std::deque<int> > *m, int p1, int p2 = 0);
int     save_ints_deque(std::deque<std::deque<int> > *m, std::deque<int> *wrangler, char **arg, int argc);
void    merge_insert_deque(std::deque<std::deque<int> > *intMatrix, size_t start = 0);
void    jacobsthal_insert_deque(std::deque<std::deque<int> > *intMatrix, std::deque<int> *jacobsthal, std::deque<int> *sequence, std::deque<int> *pend);
void    create_jacobsthall_sequence_deque(unsigned long int size, std::deque<int> *jacobsthal);
void    insert_item_deque(std::deque<int> *vec, std::deque<int> *pend, int val, int i);

// VECTOR functions:
int     duplicates_vector(std::vector<std::vector<int> > *m, int p1, int p2 = 0);
int     save_ints_vector(std::vector<std::vector<int> > *m, std::vector<int> *wrangler, char **arg, int argc);
void    merge_insert_vector(std::vector<std::vector<int> > *intMatrix, size_t start = 0);
void    jacobsthal_insert_vector(std::vector<std::vector<int> > *intMatrix, std::vector<int> *jacobsthal, std::vector<int> *sequence, std::vector<int> *pend);
void    create_jacobsthall_sequence_vector(unsigned long int size, std::vector<int> *jacobsthal);
void    insert_item_vector(std::vector<int> *vec, std::vector<int> *pend, int val, int i);


#endif