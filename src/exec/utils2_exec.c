/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq < rjacq@student.42lyon.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:21:24 by rjacq             #+#    #+#             */
/*   Updated: 2024/03/18 15:43:22 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_here_doc(t_cmd *cmd)
{
	size_t	i;

	i = -1;
	while (cmd->redirection && cmd->redirection[++i])
		if (ft_strncmp(cmd->redirection[i], "<<", 2) == 0)
			return (true);
	return (false);
}

bool	has_redir_out(t_cmd *cmd)
{
	size_t	i;

	i = -1;
	while (cmd->redirection && cmd->redirection[++i])
	{
		if (cmd->redirection[i][0] == '>')
			return (true);
	}
	return (false);
}

bool	has_redir_in(t_cmd *cmd)
{
	size_t	i;

	i = -1;
	while (cmd->redirection && cmd->redirection[++i])
	{
		if (cmd->redirection[i][0] == '<')
			return (true);
	}
	return (false);
}

void	print_error(bool mini, char *error, char *str, int exit_err)
{
	if (mini == true)
		write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	if (exit_err == 126 || exit_err == 127)
	{
		close(0);
		close(1);
	}
	exit(exit_err);
}
