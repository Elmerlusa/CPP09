# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 11:37:35 by javmarti          #+#    #+#              #
#    Updated: 2023/09/01 11:37:36 by javmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
		@echo -----ERROR-----
		./${NAME}
		./${NAME} "1 2 +" "1 2 +"ç
		./${NAME} "(1 + 1)"
		./${NAME} "(1 1 +)"
		./${NAME} "1 + 1"
		./${NAME} "+ 1 1"
		./${NAME} "1 10 +"
		./${NAME} "1 -9 +"
		@echo -----SUCCESS-----
		@echo -n 0-\>
		./${NAME} "1 2 * 2 / 2 * 2 4 - +"
		@echo -n 42-\>
		./${NAME} "8 9 * 9 - 9 - 9 - 4 - 1 +"
		@echo -n 42-\>
		./${NAME} "7 7 * 7 -"
		@echo -n 0-\>
		./${NAME} "1 2 * 2 / 2 * 2 4 - + 0 *"
		@echo -n 40-\>
		./${NAME} "3 5 + 7 2 - *"
		@echo -n 10-\>
		./${NAME} "5 6 2 4 + 1 * / * 3 + 2 +"
		@echo -n 3-\>
		./${NAME} "1 6 3 / +"
		

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
