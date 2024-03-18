/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq < rjacq@student.42lyon.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:08:35 by rjacq             #+#    #+#             */
/*   Updated: 2024/03/18 16:16:55 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_last(t_cmd *cmd, t_list **lst, int pipe1[2], t_error *err)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
		last_child(cmd, pipe1, lst, err);
	return (0);
}

static int	exec_child_pipe(t_cmd *cmd, t_list **lst, t_error *err, \
	int pipe_tab[2][2])
{
	if (pipe(pipe_tab[1]) == -1)
		return (1);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
		child_pipe(cmd, pipe_tab, lst, err);
	else
	{
		closepipe(pipe_tab[0]);
		pipe_tab[0][0] = pipe_tab[1][0];
		pipe_tab[0][1] = pipe_tab[1][1];
	}
	return (0);
}

static int	for_pipe(t_cmd *cmd, t_list **lst, int pipe_tab[2][2], t_error *err)
{
	size_t	i;

	i = 1;
	while (cmd)
	{
		if (!cmd->next)
			exec_last(cmd, lst, pipe_tab[0], err);
		else
		{
			if (exec_child_pipe(cmd, lst, err, pipe_tab) == 1)
				return (1);
		}
		if (is_here_doc(cmd))
			closepipe(cmd->pipe_dchevron);
		cmd = cmd->next;
		i++;
	}
	if (count_child(cmd) > 2)
		closepipe(pipe_tab[1]);
	return (0);
}

int	exec_pipe(t_cmd *cmd, t_list **lst, t_error *err)
{
	int	pipe_tab[2][2];

	if (for_each_here_doc(cmd, lst, err) == 1)
		return (1);
	if (pipe(pipe_tab[0]) == -1)
		return (1);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
		first_child(cmd, pipe_tab[0], lst, err);
	if (is_here_doc(cmd))
		closepipe(cmd->pipe_dchevron);
	cmd = cmd->next;
	for_pipe(cmd, lst, pipe_tab, err);
	closepipe(pipe_tab[0]);
	return (0);
}
