#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string valueFilename):
	rateFilename("data.csv"), valueFilename(valueFilename)
{
	this->readRateFilename();
	this->processValueFilename();
}

BitcoinExchange::~BitcoinExchange(void) {}

void	BitcoinExchange::readRateFilename(void)
{
	std::ifstream	ifs(this->rateFilename.c_str());
	std::string		line;
	int				lineNum = 2;

	if (ifs.is_open() == false)
		throw std::runtime_error(this->rateFilename + " not found");
	ifs >> line;
	while (ifs >> line)
	{
		if (this->validateRateDBLine(line) == false)
			std::cout << "Error: line " << lineNum << " from " << this->rateFilename << " is not correct" << std::endl;
		else
		{
			std::size_t	sep = line.find(',');

			this->dateAndRate.insert(std::pair<std::string, float>(line.substr(0, sep), atof(line.substr(sep + 1).c_str())));
		}
		lineNum++;
	}
}

void	BitcoinExchange::processValueFilename(void)
{
	std::ifstream	ifs(this->valueFilename.c_str());
	std::string		line;
	int				lineNum = 2;

	if (ifs.is_open() == false)
		throw std::runtime_error(this->valueFilename + " not found");
	std::getline(ifs, line);
	while (std::getline(ifs, line))
	{
		if (this->validateValueDBLine(line) == false)
			std::cout << "Error: line " << lineNum << " from " << this->valueFilename << " is not correct" << std::endl;
		else
			this->calculateResult(line.substr(0, line.find(' ')), atof(line.substr(line.rfind(' ')).c_str()));
		lineNum++;
	}
}

void	BitcoinExchange::calculateResult(std::string date, float value)
{
	std::map<std::string, float>::iterator	it = this->dateAndRate.find(date);
	float									result;

	if (it == this->dateAndRate.end())
		result = value * this->getClosestRate(std::pair<std::string, float>(date, value));
	else
		result = value * it->second;
	if (result >= 0 && result <= 1000)
		std::cout << date << " => " << value << " = " << result << std::endl;
	else
		std::cout << "Error: too large a number" << std::endl;
}

float	BitcoinExchange::getClosestRate(std::pair<std::string, float> p)
{
	std::map<std::string, float>::iterator	it;
	int										gapToPrevDate;
	int										gapToNextDate;
	float									rate;

	this->dateAndRate.insert(p);
	it = this->dateAndRate.find(p.first);
	if (it == this->dateAndRate.begin())
		return (++it)->second;
	else if (--it == --this->dateAndRate.end())
		return (--it)->second;
	it++;
	gapToPrevDate = std::abs(p.first.compare((--it)->first));
	it++;
	gapToNextDate = std::abs(p.first.compare((++it)->first));
	rate = gapToPrevDate < gapToNextDate ? (--it)->second : (++it)->second;
	this->dateAndRate.erase(gapToPrevDate < gapToNextDate ? ++it : --it);
	return rate;
}

bool	BitcoinExchange::validateRateDBLine(std::string line)
{
	if (line.size() < 12)
		return false;
	return	this->validateDate(line.substr(0, 10))
			&& line[10] == ','
			&& this->validateNumber(line.substr(11));
}

bool	BitcoinExchange::validateValueDBLine(std::string line)
{
	if (line.size() < 14)
		return false;
	return this->validateDate(line.substr(0, 10))
			&& line.substr(10, 3).compare(" | ") == 0
			&& this->validateNumber(line.substr(13));
}

bool	BitcoinExchange::validateDate(std::string date)
{
	return this->isDigitString(date.substr(0, 4))
			&& date[4] == '-' && date[7] == '-'
			&& this->validateMonthAndDay(date.substr(5, 2), date.substr(8, 2));
}

bool	BitcoinExchange::validateMonthAndDay(std::string month, std::string day)
{
	if (this->isDigitString(month) == false || month > "12" || month == "00"
		|| this->isDigitString(day) == false || day > "31" || day == "00")
		return false;
	switch (atoi(month.c_str()))
	{
		case 4: case 6: case 9: case 11:
			if (day > "30")
				return false;
			break ;
		case 2:
			if (day > "29")
				return false;
			break ;
		default:
			break ;
	}
	return true;
}

bool	BitcoinExchange::validateNumber(std::string rate)
{
	switch (std::count(rate.begin(), rate.end(), '.'))
	{
		case 0:
			return this->isDigitString(rate);
		case 1:
		{
			std::size_t	decimalPos = rate.find('.');

			if (decimalPos + 2 > rate.size())
				return false;
			rate.erase(rate.begin() + decimalPos);
			return this->isDigitString(rate);
		}
		default:
			return false;
	}
}

bool	BitcoinExchange::isDigitString(std::string str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}
