/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:21:43 by cassie            #+#    #+#             */
/*   Updated: 2024/03/09 14:13:26 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **cmd)
{
	int	i;
	int	j;
	bool	new_line;

	i = 1;
	j = 1;
	new_line = true;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
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
			{
				ft_putstr_fd(cmd[i], 1);
				if (cmd[i + 1])
					write(1, " ", 1);
			}
		}
		else
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
	if (new_line == true)
		write(1, "\n", 1);
	exit (0);
}
