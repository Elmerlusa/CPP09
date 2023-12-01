/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:37:52 by javmarti          #+#    #+#             */
/*   Updated: 2023/12/01 15:49:06 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void): _rateFilename(""), _valueFilename(""), _dateAndRateMap(std::map<std::string, float>())
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& bitcoinExchange):
	_rateFilename(bitcoinExchange.getRateFilename()), _valueFilename(bitcoinExchange.getValueFilename()),
	_dateAndRateMap(std::map<std::string, float>(bitcoinExchange.getDateAndRateMap()))
{
}

BitcoinExchange::BitcoinExchange(const std::string& valueFilename): _rateFilename(RATE_DB_FILENAME), _valueFilename(valueFilename)
{
	std::cout << std::fixed << std::setprecision(2);
	this->readRateFilename();
	this->processValueFilename();
}

BitcoinExchange::~BitcoinExchange(void)
{
}

const std::string&	BitcoinExchange::getRateFilename(void) const
{
	return this->_rateFilename;
}

const std::string&	BitcoinExchange::getValueFilename(void) const
{
	return this->_valueFilename;
}

const std::map<std::string, float>	BitcoinExchange::getDateAndRateMap(void) const
{
	return this->_dateAndRateMap;
}

void	BitcoinExchange::readRateFilename(void)
{
	std::ifstream	ifs(this->_rateFilename.c_str());
	std::string		line;

	if (ifs.is_open() == false)
		throw std::runtime_error(this->_rateFilename + " not found");
	ifs >> line;
	if (ifs.fail())
		throw std::runtime_error(this->_rateFilename + " is empty");
	while (ifs >> line)
	{
		std::size_t	sep;

		this->validateRateDBLine(line);
		sep = line.find(',');
		this->_dateAndRateMap.insert(std::pair<std::string, float>(line.substr(0, sep), atof(line.substr(sep + 1).c_str())));
	}
	if (this->_dateAndRateMap.size() == 0)
		throw std::runtime_error(this->_rateFilename + " is empty");
}

void	BitcoinExchange::processValueFilename(void)
{
	std::ifstream	ifs(this->_valueFilename.c_str());
	std::string		line;

	if (ifs.is_open() == false)
		throw std::runtime_error(this->_valueFilename + " not found");
	std::getline(ifs, line);
	if (ifs.fail())
		throw std::runtime_error(this->_valueFilename + " is empty");
	while (std::getline(ifs, line))
	{
		try
		{
			this->validateValueDBLine(line);
			this->calculateResult(line.substr(0, line.find(' ')), atof(line.substr(line.rfind(' ')).c_str()));
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

void	BitcoinExchange::calculateResult(const std::string& date, const float value)
{
	std::map<std::string, float>::iterator	it = this->_dateAndRateMap.find(date);
	float									result;

	if (it == this->_dateAndRateMap.end())
		result = value * this->getClosestRate(std::pair<std::string, float>(date, value));
	else
		result = value * it->second;
	std::cout << date << " => " << value << " = " << result << std::endl;
}

float	BitcoinExchange::getClosestRate(std::pair<std::string, float> p)
{
	std::map<std::string, float>::iterator	it;
	std::map<std::string, float>::iterator	itPrev;
	std::map<std::string, float>::iterator	itNext;
	float									rate;

	this->_dateAndRateMap.insert(p);
	it = this->_dateAndRateMap.find(p.first);
	if (it == this->_dateAndRateMap.begin())
	{
		rate = (++it)->second;
		it--;
	}
	else
	{
		rate = (--it)->second;
		it++;
	}
	this->_dateAndRateMap.erase(it);
	return rate;
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
	if (this->validateNumber(line.substr(13)) == false || this->validateRange(line.substr(13)) == false)
		throw std::runtime_error("Error (value DB): Incorrect value format");
}

bool	BitcoinExchange::validateRange(const std::string& num)
{
	const float	fNum = strtof(num.c_str(), NULL);
	
	return errno != ERANGE && static_cast<float>(0) <= fNum && fNum <= static_cast<float>(1000);
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

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& bitcoinExchange)
{
	if (this != &bitcoinExchange)
	{
		this->_rateFilename = bitcoinExchange.getRateFilename();
		this->_valueFilename = bitcoinExchange.getValueFilename();
		this->_dateAndRateMap = std::map<std::string, float>(bitcoinExchange.getDateAndRateMap());
	}
	return *this;
}
