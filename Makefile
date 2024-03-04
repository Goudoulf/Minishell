# **************************************************************************** #
#																			   #
#														  :::	   ::::::::    #
#	 Makefile											:+:		 :+:	:+:    #
#													  +:+ +:+		  +:+	   #
#	 By: cassie <marvin@42.fr>						+#+  +:+	   +#+		   #
#												  +#+#+#+#+#+	+#+			   #
#	 Created: 2023/12/12 12:53:45 by cassie			   #+#	  #+#			   #
#	 Updated: 2023/12/12 12:54:51 by cassie			  ###	########.fr		   #
#																			   #
# **************************************************************************** #

NAME = minishell

SRCS_FILE = main.c check_cmd.c signal.c ./utils/ft_echo.c ./utils/ft_pwd.c ./utils/list/ft_lst_add_back.c \
			./utils/list/ft_lst_clear.c ./utils/list/ft_lst_print.c ./utils/list/ft_lst_new.c\
			init/init.c ./parsing/parsing.c ./parsing/clean_line/clean_line.c \
			./parsing/split_pipe/split_pipe.c ./utils/ft_strtok.c ./parsing/line_to_cmd.c \
			./utils/count_out_in/count_out_in.c ./utils/ft_strtok_quote.c ./utils/list/ft_cmd_clear.c \
			./utils/list/ft_cmd_print.c ./parsing/find_path.c ./utils/ft_join.c \
			./utils/get_value.c ./utils/ft_export.c ./utils/ft_unset.c \
			./parsing/clean_line/add_space_chevron.c ./parsing/check_dollars.c \
			./utils/get_next_min.c ./utils/list/ft_lst_set_isprint.c ./utils/ft_exit.c init/inc_shell_lvl.c
#./exec/pipe_minishell.c 
INC = includes

FT_PRINTF_DIR = ./lib/ft_printf/

LIBFT_DIR = ./lib/libft/
DIR_SRC := src/
DIR_OBJ := .object/

OBJS = $(patsubst %.c, ${DIR_OBJ}%.o, ${SRCS})
SRCS = $(addprefix ${DIR_SRC},${SRCS_FILE})

FT_PRINTF = ./lib/ft_printf/libftprintf.a
LIBFT = ./lib/libft/libft.a
CC = cc
MD := mkdir -p
CFLAGS = -Wall -Wextra -Werror -I${INC} -g

RM = rm -rf

all: libft ft_printf ${NAME}

${NAME}: ${OBJS} ${FT_PRINTF} ${LIBFT}
	${CC} ${OBJS} -lreadline ${FT_PRINTF} ${LIBFT} -o $(NAME)

libft: ${LIBFT_DIR}
	${MAKE} -C ./lib/libft all

ft_printf: ${FT_PRINTF_DIR}
	${MAKE} -C ./lib/ft_printf all

${DIR_OBJ}%.o: %.c ${INC}/minishell.h Makefile
	mkdir -p $(shell dirname $@)
	$(CC) ${CFLAGS} -c $< -o $@

clean:
	${MAKE} -C ./lib/ft_printf clean
	${MAKE} -C ./lib/libft clean
	${RM} ${DIR_OBJ}

fclean: clean
	${MAKE} -C ./lib/ft_printf fclean
	${MAKE} -C ./lib/libft fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
