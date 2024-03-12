/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:21:43 by cassie            #+#    #+#             */
/*   Updated: 2024/03/11 17:15:36 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **cmd, int fd)
{
	int	i;
	int	j;
	bool	new_line;

	i = 1;
	j = 1;
	new_line = true;
	if (tab_size(cmd) < 2)
	{
		write(fd, "\n", 1);
		return (0);
	}
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
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (new_line == true)
		write(fd, "\n", 1);
	return (0);
}
