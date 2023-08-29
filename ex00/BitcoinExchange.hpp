#pragma once

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>

class	BitcoinExchange
{
	private:
		std::string					inputFilename;
		std::string					outputFilename;
		std::map<std::string, int>	timeAndPrice;

		void	readInputFilename(void);
		bool	validateDBLine(std::string line);
	public:
		BitcoinExchange(std::string outputFilename);
		~BitcoinExchange(void);

		
};