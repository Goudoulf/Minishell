/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq < rjacq@student.42lyon.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:52:55 by rjacq             #+#    #+#             */
/*   Updated: 2024/03/18 16:44:00 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_redirection(t_cmd *cmd, int pipe1[2], int pipe2[2], int child)
{
	size_t	i;
	int		fd[2];

	i = -1;
	fd[0] = 0;
	fd[1] = 1;
	while (cmd->redirection && cmd->redirection[++i])
	{
		if (child == 0 || child == 1)
		{
			if (cmd->redirection[i][0] == '<')
				do_input(cmd, pipe1, i, fd);
		}
		else if (child == 2 || child == 3)
		{
			if (cmd->redirection[i][0] == '<')
				do_input(cmd, pipe2, i, fd);
		}
		if (cmd->redirection[i][0] == '>')
			do_output(cmd, pipe1, i, &fd[1]);
	}
}

void	child(t_cmd *cmd, t_list **lst, t_error *err)
{
	do_redirection(cmd, NULL, NULL, 0);
	if (cmd->cmd)
		do_cmd(cmd, lst, err);
	exit (0);
}

void	last_child(t_cmd *cmd, int pipe[2], t_list **lst, t_error *err)
{
	do_redirection(cmd, pipe, NULL, 3);
	if (!has_redir_in(cmd) && !has_redir_out(cmd))
	{
		close(pipe[1]);
		dup2(pipe[0], 0);
		close(pipe[0]);
	}
	if (cmd->cmd)
		do_cmd(cmd, lst, err);
	exit (0);
}

void	first_child(t_cmd *cmd, int pipe[2], t_list **lst, t_error *err)
{
	do_redirection(cmd, pipe, NULL, 1);
	if (!has_redir_in(cmd))
	{
		close(pipe[0]);
		dup2(pipe[1], 1);
		close(pipe[1]);
	}
	if (cmd->cmd)
		do_cmd(cmd, lst, err);
	exit (0);
}

void	child_pipe(t_cmd *cmd, int pipefd[2][2], t_list **lst, t_error *err)
{
	do_redirection(cmd, pipefd[0], pipefd[1], 2);
	if (!has_redir_in(cmd))
	{
		close(pipefd[1][0]);
		dup2(pipefd[1][1], 1);
		close(pipefd[1][1]);
	}
	if (!has_redir_in(cmd) && !has_redir_out(cmd))
	{
		close(pipefd[0][1]);
		dup2(pipefd[0][0], 0);
		close(pipefd[0][0]);
	}
	if (cmd->cmd)
		do_cmd(cmd, lst, err);
	exit (0);
}
