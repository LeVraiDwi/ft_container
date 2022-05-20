SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

HEADERS = $(addprefix $(HEADER_PATH)/,$(HEADER_NAME))

CFLAGS = -Wall -Wextra -Werror -std=c++11

SRC_PATH = ./

SRC_NAME = main.cpp

HEADER_PATH = ./include

HEADER_NAME = 	iterator.hpp iteratorVector.hpp reverseIterator.hpp\
				vector.hpp algo.hpp pair.hpp\
				map.hpp mapIterator.hpp tree.hpp\
				stack.hpp\

OBJS = ${SRCS:.cpp=.o}

NAME = test_container

HEADER = -I "./include"

CC = c++

RM = rm -f

.cpp.o: 
			${CC} ${CFLAGS} ${HEADER} -c $< -o $@

${NAME}:	${OBJS} ${HEADERS}
			${CC} -o ${NAME} ${OBJS} ${FLAGS}

all:		${NAME}

clean:
			${RM} ${OBJS} ${LIBFT}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY =	all clean fclean re
