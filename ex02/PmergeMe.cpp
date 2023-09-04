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

PmergeMe::PmergeMe(char *cSeq[], int size)
{
	this->seq = cSeq;
	this->vSort(cSeq, size);
	this->dSort(cSeq, size);
	if (this->isSorted(this->v.begin(), this->v.end()) == false
		|| std::equal(this->v.begin(), this->v.end(), this->d.begin()) == false)
		throw std::runtime_error("Error");
	else
		this->printResults();
}

PmergeMe::PmergeMe(void) {}

void	PmergeMe::parseArgsToV(char *cSeq[], int size)
{
	std::vector<std::string>	seq(cSeq, cSeq + size);

	for (std::vector<std::string>::iterator it = seq.begin(); it != seq.end(); it++)
	{
		std::string	numDigits = (*it)[0] == '+' ? (*it).substr(1) : *it;

		if (numDigits.find_first_not_of("0123456789") != std::string::npos)
			throw std::runtime_error("Input error");
		else
			this->v.push_back(atoi((*it).c_str()));
	}
}

void	PmergeMe::vSort(char *cSeq[], int size)
{
	struct timespec	begin, end;

	clock_gettime(CLOCK_REALTIME, &begin);
	this->v.reserve(size);
	this->parseArgsToV(cSeq, size);
	this->vInsertionSort(this->v);
	clock_gettime(CLOCK_REALTIME, &end);
	this->vTime = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) * 1e-9;
}

void	PmergeMe::vInsertionSort(std::vector<int>& v)
{
	int	aux, tmp;

	for (std::size_t i = 0; i < v.size() - 1; i++)
	{
		if (v[i] < v[i + 1])
			continue ;
		aux = i + 1;
		while (aux > 0)
		{
			if (v[aux] > v[aux - 1])
				break ;
			tmp = v[aux];
			v[aux] = v[aux - 1];
			v[aux - 1] = tmp;
			aux--;
		}
	}
}

void	PmergeMe::dSort(char *cSeq[], int size)
{
	struct timespec	begin, end;

	clock_gettime(CLOCK_REALTIME, &begin);
	this->parseArgsToD(cSeq, size);
	this->dInsertionSort(this->d);
	clock_gettime(CLOCK_REALTIME, &end);
	this->dTime = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) * 1e-9;
}

void	PmergeMe::parseArgsToD(char *cSeq[], int size)
{
	std::deque<std::string>	seq(cSeq, cSeq + size);

	for (std::deque<std::string>::iterator it = seq.begin(); it != seq.end(); it++)
	{
		std::string	numDigits = (*it)[0] == '+' ? (*it).substr(1) : *it;

		if (numDigits.find_first_not_of("0123456789") != std::string::npos)
			throw std::runtime_error("Input error");
		else
			this->d.push_back(atoi((*it).c_str()));
	}
}

void	PmergeMe::dInsertionSort(std::deque<int>& d)
{
	int	aux, tmp;

	for (std::size_t i = 0; i < v.size() - 1; i++)
	{
		if (d[i] < d[i + 1])
			continue ;
		aux = i + 1;
		while (aux > 0)
		{
			if (d[aux] > d[aux - 1])
				break ;
			tmp = d[aux];
			d[aux] = d[aux - 1];
			d[aux - 1] = tmp;
			aux--;
		}
	}
}

void	PmergeMe::printResults(void)
{
	std::cout << std::fixed << std::setprecision(7) << "Before:\t";
	for (std::size_t i = 0; this->seq[i]; i++)
		std::cout << this->seq[i] << " ";
	std::cout << "\nAfter:\t";
	for (std::vector<int>::iterator it = this->v.begin(); it != this->v.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nTime to process a range of " << this->v.size() << " elements with std::vector<int>:\t" << this->vTime << " us\n";
	std::cout << "Time to process a range of " << this->d.size() << " elements with std::deque<int>:\t" << this->dTime << " us\n";
}
