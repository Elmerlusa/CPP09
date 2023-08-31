#pragma once

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>

#define RATE_DB_FILENAME "./dbs/oneline.csv"

class	BitcoinExchange
{
	private:
		std::string						rateFilename;
		std::string						valueFilename;
		std::map<std::string, float>	dateAndRate;

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
		BitcoinExchange(std::string valueFilename);
		~BitcoinExchange(void);
};