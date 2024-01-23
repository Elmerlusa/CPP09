/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:37:26 by javmarti          #+#    #+#             */
/*   Updated: 2023/09/01 11:37:26 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void): _v(std::vector<int>()), _vTime(0), _d(std::deque<int>()), _dTime(0)
{
}

PmergeMe::PmergeMe(const PmergeMe& pmergeMe): _v(std::vector<int>(pmergeMe.getV())), _vTime(pmergeMe.getVTime()),
	_d(std::deque<int>(pmergeMe.getD())), _dTime(pmergeMe.getDTime())
{
}

PmergeMe::PmergeMe(char *cSeq[], const int& size)
{
	this->vSort(cSeq, size);
	this->dSort(cSeq, size);
	if (this->isSorted(this->_v.begin(), this->_v.end()) == false
		|| std::equal(this->_v.begin(), this->_v.end(), this->_d.begin()) == false)
		throw std::runtime_error("Error");
	else
		this->printResults(cSeq);
}

PmergeMe::~PmergeMe(void)
{
}

const std::vector<int>&	PmergeMe::getV(void) const
{
	return this->_v;
}

const double&	PmergeMe::getVTime(void) const
{
	return this->_vTime;
}

const std::deque<int>&	PmergeMe::getD(void) const
{
	return this->_d;
}

const double&	PmergeMe::getDTime(void) const
{
	return this->_dTime;
}

void	PmergeMe::vSort(char *cSeq[], const int& size)
{
	struct timespec	begin, end;

	clock_gettime(CLOCK_REALTIME, &begin);
	this->_v.reserve(size);
	this->parseArgsToV(cSeq, size);
	this->vFordJohnsonSortAlgorithm(this->_v);
	clock_gettime(CLOCK_REALTIME, &end);
	this->_vTime = (end.tv_sec - begin.tv_sec) * 1e+3 + (end.tv_nsec - begin.tv_nsec) * 1e-6;
}

void	PmergeMe::parseArgsToV(char *cSeq[], const int& size)
{
	std::vector<std::string>	seq(cSeq, cSeq + size);

	for (std::vector<std::string>::iterator it = seq.begin(); it != seq.end(); it++)
	{
		std::string	numDigits = (*it)[0] == '+' ? (*it).substr(1) : *it;

		if (numDigits.find_first_not_of("0123456789") != std::string::npos)
			throw std::runtime_error("Error: Wrong input");
		else
			this->_v.push_back(atoi((*it).c_str()));
	}
}

void	PmergeMe::vFordJohnsonSortAlgorithm(std::vector<int>& v)
{
	vectorIntVector	pairs;
	std::vector<int>				vAux;

	this->vCreateAndSortPairs(v, pairs);
	this->vGroupLargestAndShortestValues(pairs, v, vAux);
	v.insert(v.begin(), vAux[0]);
	this->vInsertShortestValues(v, vAux);
}

void	PmergeMe::vCreateAndSortPairs(std::vector<int>& v, vectorIntVector& pairs)
{
	pairs.reserve(v.size() / 2);
	for (std::vector<int>::iterator it = v.begin(); it < v.end() - 1; std::advance(it, 2))
		pairs.push_back(std::vector<int>(it, it + 2));
	for (vectorIntVector::iterator it = pairs.begin(); it < pairs.end(); it++)
	{
		if ((*it)[0] < (*it)[1]) // swap
		{
			int	tmp = (*it)[0];

			(*it)[0] = (*it)[1];
			(*it)[1] = tmp;
		}
	}
	this->vRecursiveInsertionSort(pairs, pairs.size());
}

void	PmergeMe::vRecursiveInsertionSort(vectorIntVector& v, const size_t& n)
{
	intVector	last;
	int					index;

	if (n <= 1)
		return;
	this->vRecursiveInsertionSort(v, n - 1);
	last = v[n - 1];
	index = n - 2;
	while (index >= 0 && v[index][0] > last[0])
	{
		v[index + 1] = v[index];
		index--;
	}
	v[index + 1] = last;
}

void	PmergeMe::vGroupLargestAndShortestValues(vectorIntVector& pairs, intVector& largestV, intVector& shortestV)
{
	bool	oddSize = (largestV.size() % 2) == 1;
	int		lastValue = largestV.back();

	largestV.clear();
	for (vectorIntVector::iterator it = pairs.begin(); it < pairs.end(); it++)
	{
		largestV.push_back((*it)[0]);
		shortestV.push_back((*it)[1]);
	}
	if (oddSize)
		shortestV.push_back(lastValue);
}

void	PmergeMe::vInsertShortestValues(intVector& v, intVector& vAux)
{
	intVector	insertOrder = this->getInsertOrder(vAux.size());
	//size_t		upperBound = 3;

	for (size_t i = 0; i < insertOrder.size(); i++)
	{
		int					value = vAux[insertOrder[i]];
		intVector::iterator	insertIt = this->vBinarySearch(v, v.size() - 1, value); // cambiar

		v.insert(insertIt, value);
	}
}

std::vector<int>	PmergeMe::getInsertOrder(const size_t& size)
{
	intVector	indexes;
	size_t		i = 3;
	size_t		lastJacobsthalNum = this->getJacobsthalNum(i - 1);
	size_t		num = this->getJacobsthalNum(i);

	indexes.reserve(size);
	while (num < size)
	{
		for (size_t i = 0; i < num - lastJacobsthalNum; i++)
			indexes.push_back(num - i - 1);
		lastJacobsthalNum = num;
		num = this->getJacobsthalNum(++i);
	}
	if (std::find(indexes.begin(), indexes.end(), size - 1) == indexes.end())
	{
		for (size_t i = 0; i < size - lastJacobsthalNum; i++)
			indexes.push_back(size - i - 1);
	}
	return indexes;
}

std::vector<int>::iterator	PmergeMe::vBinarySearch(intVector& v, int end, const int& value)
{
	int	begin = 0;

	while (end - begin > 0)
	{
		int	midDistance = (end - begin) / 2;
		int	mid = begin + midDistance;

		if (value == v[mid])
			return v.begin() + midDistance;
		else if (value < v[mid])
			end = mid - 1;
		else
			begin = mid + 1;
	}
	return v.begin() + begin + (value < v[begin] ? 0 : 1);
}

void	PmergeMe::dSort(char *cSeq[], const int& size)
{
	struct timespec	begin, end;

	clock_gettime(CLOCK_REALTIME, &begin);
	this->parseArgsToD(cSeq, size);
	this->dMergeSort(this->_d, 0, this->_d.size() - 1);
	clock_gettime(CLOCK_REALTIME, &end);
	this->_dTime = (end.tv_sec - begin.tv_sec) * 1e+3 + (end.tv_nsec - begin.tv_nsec) * 1e-6;
}

void	PmergeMe::parseArgsToD(char *cSeq[], const int& size)
{
	std::deque<std::string>	seq(cSeq, cSeq + size);

	for (std::deque<std::string>::iterator it = seq.begin(); it != seq.end(); it++)
	{
		std::string	numDigits = (*it)[0] == '+' ? (*it).substr(1) : *it;

		if (numDigits.find_first_not_of("0123456789") != std::string::npos)
			throw std::runtime_error("Error: Wrong input");
		else
			this->_d.push_back(atoi((*it).c_str()));
	}
}

void	PmergeMe::dInsertionSort(std::deque<int>& d, const size_t& begin, const size_t& end)
{
	int		tmp;

	if (begin == end)
		return ;
	for (size_t i = begin; i <= end - 1; i++)
	{
		if (d[i] > d[i + 1])
		{
			tmp = d[i + 1];
			d[i + 1] = d[i];
			d[i] = tmp;
		}
	}
}

void	PmergeMe::dMergeSort(std::deque<int>& d, const size_t& begin, const size_t& end)
{
	if (end - begin <= 1)
		this->dInsertionSort(d, begin, end);
	else
	{
		size_t	mid = (begin + end) / 2;

		this->dMergeSort(d, begin, mid);
		this->dMergeSort(d, mid + 1, end);

		std::deque<int>	aux(d);
		size_t			i1 = begin;
		size_t			i2 = mid + 1;

		for (size_t i = begin; i <= end; i++)
		{
			if (i1 <= mid && (i2 > end || aux[i1] < aux[i2]))
			{
				d[i] = aux[i1];
				i1++;
			}
			else
			{
				d[i] = aux[i2];
				i2++;
			}
		}
	}
}

void	PmergeMe::printResults(char **cSeq)
{
	std::cout << std::fixed << std::setprecision(6) << "Before:\t";
	for (size_t i = 0; cSeq[i]; i++)
		std::cout << cSeq[i] << " ";
	std::cout << "\nAfter:\t";
	for (intVector::iterator it = this->_v.begin(); it != this->_v.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nTime to process a range of " << this->_v.size() << " elements with std::vector<int>:\t" << this->_vTime << " ms\n";
	std::cout << "Time to process a range of " << this->_d.size() << " elements with std::deque<int>:\t" << this->_dTime << " ms\n";
}

int	PmergeMe::getJacobsthalNum(const size_t& n)
{
	if (n == 0 || n == 1)
		return n;
	return this->getJacobsthalNum(n - 1) + 2 * getJacobsthalNum(n - 2);
}

PmergeMe&	PmergeMe::operator=(const PmergeMe& pmergeMe)
{
	if (this != &pmergeMe)
	{
		this->_v = std::vector<int>(pmergeMe.getV());
		this->_vTime = pmergeMe.getVTime();
		this->_d = std::deque<int>(pmergeMe.getD());
		this->_dTime = pmergeMe.getDTime();
	}
	return *this;
}
