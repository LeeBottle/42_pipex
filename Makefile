NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = pipex.c \
	pipex_process.c \
    pipex_funcs.c \
    pipex_utils.c \
    pipex_split.c

SRCS_BONUS = pipex_bonus.c \
	pipex_get_path.c\
	pipex_process_bonus.c \
	pipex_process_bonus2.c \
    pipex_funcs_bonus.c \
    pipex_here_doc_bonus.c \
    pipex_utils_bonus.c \
    pipex_split_bonus.c \
	get_next_line/get_next_line.c

LIBFTDIR = ./libft
LIBFTFILE = libft.a
LIBFT = $(LIBFTDIR)/$(LIBFTFILE)

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: LAST_ALL
bonus: LAST_BONUS

LAST_ALL: $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	touch $@

LAST_BONUS: $(OBJS_BONUS)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS_BONUS) $(LIBFT)
	touch $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(OBJS) $(OBJS_BONUS) LAST_ALL LAST_BONUS

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus