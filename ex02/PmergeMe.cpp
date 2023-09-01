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
	this->parseArgsToV(cSeq, size);
}

PmergeMe::PmergeMe(void) {}

void	PmergeMe::parseArgsToV(char *cSeq[], int size)
{
	std::vector<std::string>	seq;

	seq.assign(cSeq, cSeq + size);
	std::for_each(seq.begin(), seq.end(), PmergeMe::validateNumber);
}

void	PmergeMe::validateNumber(const std::string& num)
{
	std::string	numDigits = num[0] == '+' ? num.substr(1) : num;

	if (numDigits.find_first_not_of("0123456789") != std::string::npos)
		throw std::runtime_error("Input error");
}
