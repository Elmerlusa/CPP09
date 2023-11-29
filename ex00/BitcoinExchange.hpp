/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:37:54 by javmarti          #+#    #+#             */
/*   Updated: 2023/09/01 11:37:55 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>

#define RATE_DB_FILENAME "./dbs/data.csv"

class	BitcoinExchange
{
	private:
		std::string						_rateFilename;
		std::string						_valueFilename;
		std::map<std::string, float>	_dateAndRateMap;

		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange& bitcoinExchange);

		BitcoinExchange&	operator=(const BitcoinExchange& bitcoinExchange);

		const std::string&					getRateFilename(void) const;
		const std::string&					getValueFilename(void) const;
		const std::map<std::string, float>	getDateAndRateMap(void) const;

		void	readRateFilename(void);
		void	processValueFilename(void);
		void	calculateResult(const std::string& date, const float value);
		float	getClosestRate(std::pair<std::string, float> p);

		void	validateRateDBLine(const std::string& line);
		void	validateValueDBLine(const std::string& line);
		bool	validateDate(const std::string& date);
		bool	validateMonthAndDay(const std::string& month, const std::string& day);
		bool	validateNumber(std::string rate);

		bool	isDigitString(const std::string& str);
	public:
		BitcoinExchange(const std::string& valueFilename);
		~BitcoinExchange(void);
};