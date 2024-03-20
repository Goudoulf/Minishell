/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:21:43 by cassie            #+#    #+#             */
/*   Updated: 2024/03/20 09:31:36 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(char **cmd, int fd, int i)
{
	while (cmd[i])
	{
		write(fd, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(fd, " ", 1);
		i++;
	}
}

static int	newline(bool nl, t_error *err, int fd)
{
	if (nl == true)
		write(fd, "\n", 1);
	err->code = 0;
	return (0);
}

int	ft_echo(char **cmd, t_error *err, int fd, bool new_line)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i] && cmd[i][0] == '-')
	{
		j = 1;
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'n')
				break ;
			j++;
		}
		if (cmd[i][j] == '\0')
			new_line = false;
		else
			ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1] && cmd[i][j])
			write(fd, " ", 1);
		i++;
		if (new_line == true)
			break ;
	}
	print_args(cmd, fd, i);
	return (newline(new_line, err, fd));
}
