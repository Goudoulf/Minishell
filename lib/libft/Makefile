# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 14:23:58 by cassie            #+#    #+#              #
#    Updated: 2024/03/03 09:45:57 by cassie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILE = ./ft_isalpha.c ./ft_isdigit.c ./ft_isalnum.c ./ft_isascii.c \
		./ft_isprint.c ./ft_strlen.c ./ft_memset.c ./ft_bzero.c \
		./ft_memcpy.c ./ft_memmove.c ./ft_strlcpy.c ./ft_strlcat.c \
		./ft_toupper.c ./ft_tolower.c ./ft_strchr.c ./ft_strrchr.c \
		./ft_strncmp.c ./ft_memchr.c ./ft_memcmp.c ./ft_strnstr.c \
		./ft_atoi.c ./ft_calloc.c ./ft_strdup.c ./ft_substr.c \
		./ft_strjoin.c ./ft_strtrim.c ./ft_split.c ./ft_itoa.c \
		./ft_strmapi.c ./ft_striteri.c ./ft_putchar_fd.c ./ft_putstr_fd.c \
		./ft_putendl_fd.c ./ft_putnbr_fd.c

INC = includes
DIR_SRC := src/
DIR_OBJ := .object/

OBJS = $(patsubst %.c, ${DIR_OBJ}%.o, ${SRCS})
SRCS = $(addprefix ${DIR_SRC},${SRCS_FILE})

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g3 -I${INC}

NAME			= libft.a

all:			$(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

${DIR_OBJ}%.o : %.c ${INC}/libft.h Makefile
	mkdir -p $(shell dirname $@)
	${CC} ${CFLAGS} -c $< -o $@


clean:
				$(RM) -R ${DIR_OBJ}

fclean:			clean
				$(RM) $(NAME)

re:			fclean all

.PHONY:			all clean fclean re
