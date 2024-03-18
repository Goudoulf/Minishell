/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq < rjacq@student.42lyon.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:20:11 by rjacq             #+#    #+#             */
/*   Updated: 2024/03/18 15:20:52 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	last_redir_in(t_cmd *cmd)
{
	size_t	i;
	size_t	index_last;

	i = 0;
	index_last = 0;
	while (cmd->redirection[i])
	{
		if (cmd->redirection[i][0] == '<')
			index_last = i;
		i++;
	}
	return (index_last);
}

size_t	last_redir_out(t_cmd *cmd)
{
	size_t	i;
	size_t	index_last;

	i = 0;
	index_last = 0;
	while (cmd->redirection[i])
	{
		if (cmd->redirection[i][0] == '>')
			index_last = i;
		i++;
	}
	return (index_last);
}

size_t	count_child(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	isdirectory(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	closepipe(int pipe[2])
{
	if (close(pipe[0]) == -1)
		perror(ft_itoa(pipe[0]));
	if (close(pipe[1]) == -1)
		perror(ft_itoa(pipe[1]));
}
