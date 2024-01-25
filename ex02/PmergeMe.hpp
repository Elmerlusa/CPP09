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
#include <cmath>

class	PmergeMe
{
	private:
		std::vector<int>	_v;
		double				_vTime;
		std::deque<int>		_d;
		double				_dTime;

		PmergeMe(void);
		PmergeMe(const PmergeMe& pmergeMe);

		PmergeMe&	operator=(const PmergeMe& pmergeMe);

		const std::vector<int>&	getV(void) const;
		const double&			getVTime(void) const;
		const std::deque<int>&	getD(void) const;
		const double&			getDTime(void) const;

		void	vSort(char *cSeq[], const int& size);
		void	parseArgsToV(char *cSeq[], const int& size);
		void	vFordJohnsonSortAlgorithm(std::vector<int>& v);
		void	vCreateAndSortPairs(std::vector<int>& v, std::vector< std::vector<int> >& pairs);
		void	vGroupLargestAndShortestValues(std::vector< std::vector<int> >& pairs, std::vector<int>& largestV, std::vector<int>& shortestV);
		void	vRecursiveInsertionSort(std::vector< std::vector<int> >& v, const size_t& n);
		void	vInsertShortestValues(std::vector<int>& v, std::vector<int>& vAux);
		std::vector<int>	vGetInsertOrder(const size_t& size);
		std::vector<int>::iterator	vBinarySearch(std::vector<int>& v, int end, const int& value);

		void	dSort(char *cSeq[], const int& size);
		void	parseArgsToD(char *cSeq[], const int& size);
		void	dFordJohnsonSortAlgorithm(std::deque<int>& d);
		void	dCreateAndSortPairs(std::deque<int>& d, std::deque< std::deque<int> >& pairs);
		void	dGroupLargestAndShortestValues(std::deque< std::deque<int> >& pairs, std::deque<int>& largestD, std::deque<int>& shortestD);
		void	dRecursiveInsertionSort(std::deque< std::deque<int> >& d, const size_t& n);
		void	dInsertShortestValues(std::deque<int>& d, std::deque<int>& dAux);
		std::deque<int>	dGetInsertOrder(const size_t& size);
		std::deque<int>::iterator	dBinarySearch(std::deque<int>& d, int end, const int& value);

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
