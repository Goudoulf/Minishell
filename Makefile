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

SRCS_FILE =

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
	${CC} ${OBJS} ${FT_PRINTF} ${LIBFT} -o $(NAME)

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
