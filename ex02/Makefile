# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 11:37:28 by javmarti          #+#    #+#              #
#    Updated: 2024/01/25 10:38:18 by javmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PmergeMe

CPP = c++
FLAGS = -Wall -Wextra -Werror -std=c++98

CPPF = main.cpp PmergeMe.cpp
CPPO = ${CPPF:.cpp=.o}

RM = rm -rf
########################################################
.PHONY: all test re fclean clean
########################################################
all:		${NAME}

test:		${NAME}
		@clear
		./${NAME}
		./${NAME} a
		./${NAME} 1+
		./${NAME} -1 2
		./${NAME} 1
		./${NAME} 1 2
		./${NAME} 0 0 1
		./${NAME} 1 2 3 4 5 6 7
		./${NAME} 1 2 3 4 5 6 7 8 9
		@read a
		@clear
		./${NAME} `jot -r 10 1 100 | tr "\n" " "`
		./${NAME} `jot -r 10 1 100 | tr "\n" " "`
		./${NAME} `jot -r 10 1 100 | tr "\n" " "`
		./${NAME} `jot -r 10 1 100 | tr "\n" " "`
		./${NAME} `jot -r 10 1 100 | tr "\n" " "`
		./${NAME} `jot -r 10 1 100 | tr "\n" " "`
		@read a
		@clear
		./${NAME} `jot -r 3000 1 100000 | tr "\n" " "`
		@read a
		@clear
		./${NAME} `jot -r 5000 1 100000 | tr "\n" " "`
		
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