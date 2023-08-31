NAME = RPN

CPP = c++
FLAGS = -Wall -Wextra -Werror -std=c++98

CPPF = main.cpp RPN.cpp
CPPO = ${CPPF:.cpp=.o}

RM = rm -rf
########################################################
.PHONY: all test re fclean clean
########################################################
all:		${NAME}

test:		${NAME}
		./${NAME}

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