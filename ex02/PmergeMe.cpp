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

PmergeMe::PmergeMe(void): _v(std::vector<int>()), _vTime(0), _d(std::deque<int>()), _dTime()
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

void	PmergeMe::vSort(char *cSeq[], const int& size)
{
	struct timespec	begin, end;

	clock_gettime(CLOCK_REALTIME, &begin);
	this->_v.reserve(size);
	this->parseArgsToV(cSeq, size);
	this->vMergeSort(this->_v, 0, this->_v.size() - 1);
	clock_gettime(CLOCK_REALTIME, &end);
	this->_vTime = (end.tv_sec - begin.tv_sec) * 1e+3 + (end.tv_nsec - begin.tv_nsec) * 1e-6;
}

void	PmergeMe::vInsertionSort(std::vector<int>& v, const size_t& begin, const size_t& end)
{
	size_t	aux;
	int		tmp;

	if (begin == end)
		return ;
	for (std::size_t i = begin; i <= end - 1; i++)
	{
		if (v[i] < v[i + 1])
			continue ;
		aux = i + 1;
		tmp = v[i + 1];
		while (aux > begin && tmp < v[aux - 1])
		{
			v[aux] = v[aux - 1];
			aux--;
		}
		v[aux] = tmp;
	}
}

void	PmergeMe::vMergeSort(std::vector<int>& v, const size_t& begin, const size_t& end)
{
	if (end - begin <= SORT_TRESHOLD)
		this->vInsertionSort(v, begin, end);
	else
	{
		size_t	mid = (begin + end) / 2;

		this->vMergeSort(v, begin, mid);
		this->vMergeSort(v, mid + 1, end);

		std::vector<int>	aux(v);
		size_t				i1 = begin;
		size_t				i2 = mid + 1;

		for (size_t i = begin; i <= end; i++)
		{
			if (i1 <= mid && (i2 > end || aux[i1] < aux[i2]))
			{
				v[i] = aux[i1];
				i1++;
			}
			else
			{
				v[i] = aux[i2];
				i2++;
			}
		}
	}
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
	size_t	aux;
	int		tmp;

	if (begin == end)
		return ;
	for (std::size_t i = begin; i <= end - 1; i++)
	{
		if (d[i] < d[i + 1])
			continue ;
		aux = i + 1;
		tmp = d[i + 1];
		while (aux > begin && tmp < d[aux - 1])
		{
			d[aux] = d[aux - 1];
			aux--;
		}
		d[aux] = tmp;
	}
}

void	PmergeMe::dMergeSort(std::deque<int>& d, const size_t& begin, const size_t& end)
{
	if (end - begin <= SORT_TRESHOLD)
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
	for (std::size_t i = 0; cSeq[i]; i++)
		std::cout << cSeq[i] << " ";
	std::cout << "\nAfter:\t";
	for (std::vector<int>::iterator it = this->_v.begin(); it != this->_v.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nTime to process a range of " << this->_v.size() << " elements with std::vector<int>:\t" << this->_vTime << " ms\n";
	std::cout << "Time to process a range of " << this->_d.size() << " elements with std::deque<int>:\t" << this->_dTime << " ms\n";
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
