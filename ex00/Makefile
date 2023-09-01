# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 11:37:57 by javmarti          #+#    #+#              #
#    Updated: 2023/09/01 11:37:58 by javmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
		./${NAME} ./dbs/input.txt

error:		${NAME}
		./${NAME}
		./${NAME} a
		./${NAME} a b

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