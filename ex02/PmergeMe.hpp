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
#include <math.h>

class	PmergeMe
{
	private:
		std::vector<int>	_v;
		double				_vTime;
		std::deque<int>		_d;
		double				_dTime;

		typedef typename std::vector<int>					intVector;
		typedef typename std::vector< std::vector<int> >	vectorIntVector;

		PmergeMe(void);
		PmergeMe(const PmergeMe& pmergeMe);

		PmergeMe&	operator=(const PmergeMe& pmergeMe);

		const std::vector<int>&	getV(void) const;
		const double&			getVTime(void) const;
		const std::deque<int>&	getD(void) const;
		const double&			getDTime(void) const;

		void	vSort(char *cSeq[], const int& size);
		void	parseArgsToV(char *cSeq[], const int& size);
		void	vFordJohnsonSortAlgorithm(intVector& v);
		void	vCreateAndSortPairs(intVector& v, vectorIntVector& pairs);
		void	vGroupLargestAndShortestValues(vectorIntVector& pairs, intVector& largestV, intVector& shortestV);
		void	vRecursiveInsertionSort(vectorIntVector& v, const size_t& n);
		void	vInsertShortestValues(intVector& v, intVector& vAux);
		intVector	getInsertOrder(const size_t& size);
		intVector::iterator	vBinarySearch(intVector& v, int end, const int& value);

		void	parseArgsToD(char *cSeq[], const int& size);
		void	dSort(char *cSeq[], const int& size);
		void	dInsertionSort(std::deque<int>& d, const size_t& begin, const size_t& end);
		void	dMergeSort(std::deque<int>& d, const size_t& begin, const size_t& end);

		void	printResults(char **cSeq);

		int					getJacobsthalNum(const size_t& n);

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
		PmergeMe(char *cSeq[], const int& size);
		~PmergeMe(void);
};
