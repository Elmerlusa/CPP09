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

		void	parseArgsToV(char *cSeq[], const int& size);
		void	vSort(char *cSeq[], const int& size);
		void	swap(std::vector<int>& v, const size_t& i1, const size_t& i2);
		std::vector<int>	vGroupLargestAndShortestValues(std::vector<int>& v, std::vector< std::vector<int> > &pairs);
		void	insertShortestValues(std::vector<int>& v, const std::vector<int>& vAux);
		std::vector< std::vector<int> >	vCreateAndSortPairs(std::vector<int>& v);
		void	vRecursiveInsertionSort(std::vector< std::vector<int> >& v, int n);
		void	vFordJohnsonSortAlgorithm(std::vector<int>& v);

		void	parseArgsToD(char *cSeq[], const int& size);
		void	dSort(char *cSeq[], const int& size);
		void	dInsertionSort(std::deque<int>& d, const size_t& begin, const size_t& end);
		void	dMergeSort(std::deque<int>& d, const size_t& begin, const size_t& end);

		void	printResults(char **cSeq);

		int		getJacobsthalNum(const size_t& n);
		std::vector<int>	getInsertOrder(const size_t& size);

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
