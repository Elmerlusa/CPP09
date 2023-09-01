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

RPN::RPN(std::string rpn)
{
	this->calculateRPN(rpn);
}

RPN::~RPN(void) {}

void	RPN::calculateRPN(const std::string& rpn)
{
	std::stack<int>	s;
	std::stringstream	ss(rpn);
	char				c;
	std::string			validOps = "+-/*";

	while (ss >> c)
	{
		bool	isOperator = validOps.find(c) != std::string::npos;

		if (ss.fail() || (std::isdigit(c) == false && isOperator == false))
			throw std::runtime_error("Error");
		if (isOperator)
			this->doOperation(s, c);
		else
			s.push(c - '0');
	}
	if (s.size() != 1)
		throw std::runtime_error("Error");
	std::cout << s.top() << std::endl;
}

void	RPN::doOperation(std::stack<int>& s, char op)
{
	int	firstOperand;
	int	secondOperand;

	if (s.size() < 2)
		throw std::runtime_error("Error");
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
			s.push(firstOperand / secondOperand);
			break ;
		case '*':
			s.push(firstOperand * secondOperand);
	}
}
