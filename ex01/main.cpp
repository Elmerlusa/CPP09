#include "RPN.hpp"

int	main(int argc, char *argv[])
{
	if (argc != 2)
		std::cout << "Wrong number of parameters" << std::endl;
	else
	{
		try
		{
			RPN	r(argv[1]);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		
	}
	return 0;
}
