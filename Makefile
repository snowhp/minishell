SRCS =  src/minishell.c \
		src/signals/signals.c \
		src/checkline.c \
		src/commands/commands.c \
		src/commands/commands2.c \
		src/commands/execute.c \
		src/commands/execute2.c \
		src/commands/expand.c \
		src/commands/expand2.c \
		src/commands/expand3.c \
		src/commands/expand4.c \
		src/commands/expand5.c \
		src/commands/parse.c \
		src/commands/parse2.c \
		src/commands/check.c \
		src/commands/ft_splitargs.c \
		src/commands/ft_splitargs2.c \
		src/builtins/cd.c \
		src/builtins/env.c \
		src/builtins/env2.c \
		src/builtins/unset.c \
		src/builtins/echo.c \
		src/builtins/exit.c \
		src/builtins/export.c \
		src/builtins/export2.c \
		src/builtins/export3.c

OBJS = $(SRCS:.c=.o)

NAME = minishell
LIBFT		= libft.a
LIBFT_DIR := ./libft
LIBFT_LIB := $(LIBFT_DIR)/libft.a
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(FLAGS) $(OBJS) -lreadline $(LIBFT_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

debug: $(OBJS) $(LIBFT_LIB)
	$(CC) $(FLAGS) -g $(SRCS) libft/*.c -lreadline -o $(NAME)

sanitize: $(OBJS) $(LIBFT_LIB)
	$(CC) $(FLAGS) -g -fsanitize=address $(SRCS) libft/*.c -lreadline -o $(NAME)


$(LIBFT_LIB):
	cd $(LIBFT_DIR) && $(MAKE)

clean:
	cd $(LIBFT_DIR) && $(MAKE) clean
	$(RM) $(OBJS)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline_supression ./minishell

fclean: clean
	cd $(LIBFT_DIR) && $(MAKE) fclean
	$(RM) $(NAME)

re: fclean all
