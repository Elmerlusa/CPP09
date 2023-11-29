/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:37:38 by javmarti          #+#    #+#             */
/*   Updated: 2023/09/01 11:37:39 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <stack>
#include <sstream>

class	RPN
{
	private:
		RPN(const RPN& rpn);
		RPN(const std::string& args);
		~RPN(void);

		RPN&	operator=(const RPN& rpn);

		static void	doOperation(std::stack<int>& s, char op);

		virtual void	makeAbstract(void) const = 0;
	public:
		static void	calculateRPN(const std::string& rpn);
};
