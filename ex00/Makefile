NAME = btc

CPP = c++
FLAGS = -Wall -Wextra -Werror -std=c++98

CPPF = main.cpp BitcoinExchange.cpp
CPPO = ${CPPF:.cpp=.o}

RM = rm -rf
########################################################
.PHONY: all test error re fclean clean
########################################################
all:		${NAME}

test:		${NAME}
		./${NAME} data.csv

error:		${NAME}
		./${NAME}
		./${NAME} a

${NAME}:	${CPPO}
		@${CPP} ${FLAGS} ${CPPO} -o ${NAME}

%.o: 		%.cpp
		@$(CPP) $(FLAGS) -c $< -o $@

re:			fclean all

fclean:		clean
		@${RM} ${NAME}

clean:
		@${RM} ${CPPO}
########################################################