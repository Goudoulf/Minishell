# **************************************************************************** #
#									       #
#							  :::	   ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#						      +:+ +:+	      +:+      #
#    By: cassie <marvin@42.fr>			    +#+  +:+	   +#+	       #
#						  +#+#+#+#+#+	+#+	       #
#    Created: 2023/11/28 11:13:50 by cassie	       #+#    #+#	       #
#    Updated: 2024/02/05 12:46:40 by cassie           ###   ########.fr        #
#									       #
# **************************************************************************** #

SRCS_FILE = ft_printf.c \
		ft_printf_hexa.c \
		ft_printf_putchar.c \
		ft_printf_putstr.c \
		ft_printf_putnbr.c \
		ft_printf_strlen.c \
		ft_printf_hexa_ptr.c \
		ft_unsigned_putnbr.c \

INC	= includes

DIR_SRC := src/
DIR_OBJ := .object/

OBJS = $(patsubst %.c, ${DIR_OBJ}%.o, ${SRCS})
SRCS = $(addprefix ${DIR_SRC},${SRCS_FILE})

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I${INC}

NAME			= libftprintf.a

all:			$(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

${DIR_OBJ}%.o : %.c ${INC}/ft_printf.h Makefile
	mkdir -p $(shell dirname $@)
	${CC} ${CFLAGS} -c $< -o $@

clean:
				$(RM) -R $(DIR_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:			fclean all

.PHONY:			all clean fclean re

