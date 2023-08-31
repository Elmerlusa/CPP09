#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string valueFilename):
	rateFilename(RATE_DB_FILENAME), valueFilename(valueFilename)
{
	this->readRateFilename();
	this->processValueFilename();
}

BitcoinExchange::~BitcoinExchange(void) {}

void	BitcoinExchange::readRateFilename(void)
{
	std::ifstream	ifs(this->rateFilename.c_str());
	std::string		line;

	if (ifs.is_open() == false)
		throw std::runtime_error(this->rateFilename + " not found");
	ifs >> line;
	while (ifs >> line)
	{
		std::size_t	sep;

		std::cout << "->" << line << std::endl;
		this->validateRateDBLine(line);
		sep = line.find(',');
		this->dateAndRate.insert(std::pair<std::string, float>(line.substr(0, sep), atof(line.substr(sep + 1).c_str())));
	}
	if (this->dateAndRate.size() == 0)
		throw std::runtime_error(this->rateFilename + " is empty");
}

void	BitcoinExchange::processValueFilename(void)
{
	std::ifstream	ifs(this->valueFilename.c_str());
	std::string		line;

	if (ifs.is_open() == false)
		throw std::runtime_error(this->valueFilename + " not found");
	std::getline(ifs, line);
	while (std::getline(ifs, line))
	{
		try
		{
			this->validateValueDBLine(line);
			this->calculateResult(line.substr(0, line.find(' ')), atof(line.substr(line.rfind(' ')).c_str()));
			std::map<std::string, float>::iterator	it = this->dateAndRate.begin();
			for (; it != this->dateAndRate.end(); it++)
				std::cout << "map entry:" << it->first << ", " << it->second << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

void	BitcoinExchange::calculateResult(const std::string& date, const float value)
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
		throw std::runtime_error("Error (result): too large a number");
}

float	BitcoinExchange::getClosestRate(std::pair<std::string, float> p)
{
	std::map<std::string, float>::iterator	it;
	std::map<std::string, float>::iterator	itPrev;
	std::map<std::string, float>::iterator	itNext;
	int										gapToPrevDate;
	int										gapToNextDate;

	this->dateAndRate.insert(p);
	it = this->dateAndRate.find(p.first);
	if (it == this->dateAndRate.begin())
		return (++it)->second;
	else if (it == --this->dateAndRate.end())
		return (--it)->second;
	itNext = it;
	itNext++;
	itPrev = it;
	itPrev--;
	this->dateAndRate.erase(it);
	gapToPrevDate = std::abs(p.first.compare(itPrev->first));
	gapToNextDate = std::abs(p.first.compare(itNext->first));
	return gapToPrevDate < gapToNextDate ? itPrev->second : itNext->second;
}

void	BitcoinExchange::validateRateDBLine(const std::string& line)
{
	if (line.size() < 12 || line[10] != ',')
		throw std::runtime_error("Error (rate DB): Incorrect line format");
	if (this->validateDate(line.substr(0, 10)) == false)
		throw std::runtime_error("Error (rate DB): Incorrect date format");
	if (this->validateNumber(line.substr(11)) == false)
		throw std::runtime_error("Error (rate DB): Incorrect rate format");
}

void	BitcoinExchange::validateValueDBLine(const std::string& line)
{
	if (line.size() < 14 || line.substr(10, 3).compare(" | ") != 0)
		throw std::runtime_error("Error (value DB): Incorrect line format");
	if (this->validateDate(line.substr(0, 10)) == false)
		throw std::runtime_error("Error (value DB): Incorrect date format");
	if (this->validateNumber(line.substr(13)) == false)
		throw std::runtime_error("Error (value DB): Incorrect value format");
}

bool	BitcoinExchange::validateDate(const std::string& date)
{
	return this->isDigitString(date.substr(0, 4))
			&& date[4] == '-' && date[7] == '-'
			&& this->validateMonthAndDay(date.substr(5, 2), date.substr(8, 2));
}

bool	BitcoinExchange::validateMonthAndDay(const std::string& month, const std::string& day)
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

bool	BitcoinExchange::isDigitString(const std::string& str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}
