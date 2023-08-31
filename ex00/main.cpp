#include "BitcoinExchange.hpp"

int	main(int argc, char *argv[])
{
	if (argc != 2)
		std::cout << "One file must be provided" << std::endl;
	else
	{
		try
		{
			BitcoinExchange	btc(argv[1]);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return 0;
}