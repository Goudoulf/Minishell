/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:21:43 by cassie            #+#    #+#             */
/*   Updated: 2024/03/14 09:08:28 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **cmd, t_error *err)
{
	int	i;
	int	j;
	bool	new_line;

	i = 1;
	j = 1;
	new_line = true;
	if (tab_size(cmd) < 2)
	{
		write(1, "\n", 1);
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
			ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1] && cmd[i][j])
			write(1, " ", 1);
		i++;
		if (new_line == true)
			break ;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line == true)
		write(1, "\n", 1);
	err->code = 0;
	return (0);
}
