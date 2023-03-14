SRCS 	=	src/init.c src/main.c src/monitoring.c \
			src/parsing.c src/utils.c src/routine.c \

OBJ		=	$(SRCS:.c=.o)

CC		=	@cc
RM		=	@rm -rf
CFLAGS	=	-Wall -Werror -Wextra -I./includes

NAME	=	philo

all:		$(NAME)

$(NAME):	$(OBJ)
				@echo "\n"
				@echo "\033[32m$ ----- Le diner est servi ! -----"
				@echo "\n"
				$(CC) $(OBJ) -lpthread -o $(NAME)

clean:
				@$(RM) $(OBJ)

fclean:		clean
				$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re