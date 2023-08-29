#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string outputFilename):
	inputFilename("data.csv"), outputFilename(outputFilename)
{
	try
	{
		this->readInputFilename();
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

BitcoinExchange::~BitcoinExchange(void) {}

void	BitcoinExchange::readInputFilename(void)
{
	std::ifstream	ifs(this->inputFilename.c_str());
	std::string		line;

	if (ifs.is_open() == false)
		throw std::runtime_error("File not found");
	ifs >> line;
	while (ifs >> line)
	{
		std::cout << "DBLINE: " << line << " - " << this->validateDBLine(line) << std::endl;
	}
}

bool	BitcoinExchange::validateDBLine(std::string line)
{
	if (line.size() < 12)
		throw std::runtime_error("Wrong data format");
}
