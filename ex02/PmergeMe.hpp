/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:37:30 by javmarti          #+#    #+#             */
/*   Updated: 2023/09/01 11:37:30 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <iomanip>

#define SORT_TRESHOLD 12

class	PmergeMe
{
	private:
		char**				seq;
		std::vector<int>	v;
		double				vTime;
		std::deque<int>		d;
		double				dTime;

		void	parseArgsToV(char *cSeq[], int size);
		void	vSort(char *cSeq[], int size);
		void	vInsertionSort(std::vector<int>& v, size_t begin, size_t end);
		void	vMergeSort(std::vector<int>& v, size_t begin, size_t end);

		void	parseArgsToD(char *cSeq[], int size);
		void	dSort(char *cSeq[], int size);
		void	dInsertionSort(std::deque<int>& d, size_t begin, size_t end);
		void	dMergeSort(std::deque<int>& d, size_t begin, size_t end);

		void	printResults(void);

		template<class InputIt> bool	isSorted(InputIt begin, InputIt end)
		{
			end--;
			while (begin != end)
			{
				if (*begin > *(begin + 1))
					return false;
				begin++;
			}
			return true;
		}
	public:
		PmergeMe(char *cSeq[], int size);
		PmergeMe(void);
};
