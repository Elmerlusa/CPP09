/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:37:33 by javmarti          #+#    #+#             */
/*   Updated: 2023/09/01 11:37:34 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int argc, char *argv[])
{
	if (argc != 2)
		std::cout << "Wrong number of parameters" << std::endl;
	else
	{
		try
		{
			RPN::calculateRPN(argv[1]);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}
	return 0;
}
