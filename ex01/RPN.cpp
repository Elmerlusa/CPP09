/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:37:36 by javmarti          #+#    #+#             */
/*   Updated: 2023/09/01 11:37:38 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(const RPN& rpn)
{
	(void) rpn;
}

RPN::RPN(const std::string& rpn)
{
	this->calculateRPN(rpn);
}

RPN::~RPN(void)
{
}

void	RPN::doOperation(std::stack<int>& s, char op)
{
	int	firstOperand;
	int	secondOperand;

	if (s.size() < 2)
		throw std::runtime_error("Error: Wrong RPN");
	secondOperand = s.top();
	s.pop();
	firstOperand = s.top();
	s.pop();
	switch (op)
	{
		case '+':
			s.push(firstOperand + secondOperand);
			break ;
		case '-':
			s.push(firstOperand - secondOperand);
			break ;
		case '/':
			if (secondOperand == 0)
				throw std::runtime_error("Error: Cannot divide by 0");
			s.push(firstOperand / secondOperand);
			break ;
		case '*':
			s.push(firstOperand * secondOperand);
	}
}

void	RPN::calculateRPN(const std::string& rpn)
{
	std::stack<int>	s;
	std::stringstream	ss(rpn);
	char				c;
	std::string			validOps = "+-/*";

	while (ss >> c)
	{
		if (ss.fail())
			throw std::runtime_error("Error");
		if (std::isdigit(c) == false && validOps.find(c) == std::string::npos)
			throw std::runtime_error("Error: Wrong RPN");
		if (validOps.find(c) != std::string::npos)
			RPN::doOperation(s, c);
		else
			s.push(c - '0');
	}
	if (s.size() != 1)
		throw std::runtime_error("Error: Wrong RPN");
	std::cout << s.top() << std::endl;
}

RPN&	RPN::operator=(const RPN& rpn)
{
	(void) rpn;
	return *this;
}
