NAME	= push_swap
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRCS	=	main.c \
			parse.c \
			ft_utils.c \
			ft_split.c \
			stack_init.c \
			stack_utils.c \
			op_swap.c \
			op_push.c \
			op_rotate.c \
			op_rev_rotate.c \
			sort.c \
			sort_insert.c \
			sort_exec.c \
			sort_large.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
