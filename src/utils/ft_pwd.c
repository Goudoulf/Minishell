/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 08:03:34 by cassie            #+#    #+#             */
/*   Updated: 2024/03/19 15:43:47 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_pwd(char *s, int fd, t_error *err)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
	free(s);
	err->code = 0;
	return (0);
}

int	ft_pwd(t_error *err, int fd, int size, int i)
{
	char	*str;
	char	*temp;

	str = malloc(sizeof(char) * size + 1);
	if (!str)
		quit_error(err);
	while (i * size < 4096)
	{
		temp = getcwd(str, size * i);
		if (!temp)
		{
			free(str);
			i++;
			str = malloc(sizeof(char) * size * i + 1);
			if (!str)
				quit_error(err);
		}
		else
			return (print_pwd(temp, fd, err));
	}
	free(str);
	err->code = 0;
	return (0);
}
