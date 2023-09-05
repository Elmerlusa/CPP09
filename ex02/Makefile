# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 11:37:28 by javmarti          #+#    #+#              #
#    Updated: 2023/09/01 11:40:33 by javmarti         ###   ########.fr        #
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
		./${NAME}
		./${NAME} a
		./${NAME} 1+
		./${NAME} "-1" "2"
		./${NAME} 1
		./${NAME} 0 0 1
		./${NAME} 1 2 3 4 3 3 7
		./${NAME} 0 2
		./${NAME} 1 2 3 4 5 6 7 8 9
		./${NAME} `shuf -i 1-100 -n 10 | tr "\n" " "`
		@read a
		./${NAME} `shuf -i 1-100000 -n 3000 | tr "\n" " "`
		@read b
		./${NAME} `shuf -i 1-100000 -n 5000 | tr "\n" " "`

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