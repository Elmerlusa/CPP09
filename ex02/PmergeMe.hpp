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
#include <sstream>
#include <stdexcept>
#include <algorithm>

class	PmergeMe
{
	private:
		std::vector<unsigned int>	v;

		void	parseArgsToV(char *cSeq[], int size);
	public:
		PmergeMe(char *cSeq[], int size);
		PmergeMe(void);

		static void	validateNumber(const std::string& num);
};
