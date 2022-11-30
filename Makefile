SRCS 	=	src/main.c src/utils.c src/parsing.c \

OBJ		=	$(SRCS:.c=.o)

CC		=	cc
RM		=	rm -rf
CFLAGS	=	-Wall -Werror -Wextra -I./includes

NAME	=	philo

all:		$(NAME)

$(NAME):	$(OBJ)
				$(CC) $(OBJ) -lpthread -o $(NAME)

clean:
				$(RM) $(OBJ)

fclean:		clean
				$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re