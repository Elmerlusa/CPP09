#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <stack>
#include <sstream>

class	RPN
{
	private:
		void	calculateRPN(const std::string& rpn);
		void	doOperation(std::stack<int>& s, char op);
	public:
		RPN(std::string args);
		~RPN(void);
};
