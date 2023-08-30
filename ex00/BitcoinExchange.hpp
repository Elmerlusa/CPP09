#pragma once

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>

class	BitcoinExchange
{
	private:
		std::string						rateFilename;
		std::string						valueFilename;
		std::map<std::string, float>	dateAndRate;

		void	readRateFilename(void);
		void	processValueFilename(void);
		void	calculateResult(std::string date, float value);
		float	getClosestRate(std::pair<std::string, float> p);

		bool	validateRateDBLine(std::string line);
		bool	validateValueDBLine(std::string line);
		bool	validateDate(std::string date);
		bool	validateMonthAndDay(std::string month, std::string day);
		bool	validateNumber(std::string rate);

		bool	isDigitString(std::string str);
	public:
		BitcoinExchange(std::string valueFilename);
		~BitcoinExchange(void);
};