/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:19:08 by rjacq             #+#    #+#             */
/*   Updated: 2024/03/19 15:42:09 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_input(int fd, int pipe[2], t_cmd *cmd)
{
	if (fd != 0)
	{
		if (dup2(fd, 0) == -1)
		{
			perror(ft_itoa(fd));
			closepipe(pipe);
			exit(1);
		}
		if (close(fd) == -1)
			perror(ft_itoa(fd));
	}
	if ((pipe && !is_here_doc(cmd) && !has_redir_out(cmd)) || cmd->next)
	{
		if (close(pipe[0]) == -1)
			perror(ft_itoa(pipe[0]));
		if (dup2(pipe[1], 1) == -1)
		{
			perror(ft_itoa(fd));
			closepipe(pipe);
			exit(1);
		}
		if (close(pipe[1]) == -1)
			perror(ft_itoa(pipe[1]));
	}
}

void	do_input(t_cmd *cmd, int pipe[2], size_t i, int *fd)
{
	if (*fd != 0)
		if (close(*fd) == -1)
			perror(ft_itoa(*fd));
	if (ft_strncmp(cmd->redirection[i], "<<", 2) == 0)
	{
		if (close(cmd->pipe_dchevron[1]) == -1)
			perror(ft_itoa(cmd->pipe_dchevron[1]));
		*fd = cmd->pipe_dchevron[0];
	}
	else if (cmd->redirection[i][0] == '<')
		*fd = open(&cmd->redirection[i][1], O_RDONLY);
	if (*fd == -1)
	{
		if (errno == 2)
			print_error(true, "No such file or directory", \
				&cmd->redirection[i][1], 1);
		else
			print_error(true, "Permission denied", &cmd->redirection[i][1], 1);
	}
	if (i == last_redir_out(cmd) && \
		(!pipe || (pipe && pipe[0] != -2 && pipe[1] != -2)))
		redir_input(*fd, pipe, cmd);
}

static void	redir_output(int fd, int pipe[2], t_cmd *cmd)
{
	if (fd != 1)
	{
		if (dup2(fd, 1) == -1)
		{
			perror(ft_itoa(fd));
			closepipe(pipe);
			exit(1);
		}
		if (close(fd) == -1)
			perror(ft_itoa(fd));
	}
	if (pipe && !has_redir_in(cmd))
	{
		if (close(pipe[1]) == -1)
			perror(ft_itoa(pipe[1]));
		if (dup2(pipe[0], 0) == -1)
		{
			perror(ft_itoa(pipe[0]));
			closepipe(pipe);
			exit(1);
		}
		if (close(pipe[0]) == -1)
			perror(ft_itoa(pipe[0]));
	}
}

void	do_output(t_cmd *cmd, int pipe[2], size_t i, int *fd)
{
	int	j;

	j = 1;
	if (*fd != 1)
		if (close(*fd) == -1)
			perror(ft_itoa(*fd));
	if (ft_strncmp(cmd->redirection[i], ">>", 2) == 0)
		*fd = open(&cmd->redirection[i][++j], O_CREAT | O_RDWR | \
			O_APPEND, 00644);
	else if (cmd->redirection[i][0] == '>')
		*fd = open(&cmd->redirection[i][j], O_CREAT | O_RDWR | \
			O_TRUNC, 00644);
	if (*fd == -1)
	{
		if (errno == 2)
			print_error(true, "No such file or directory", \
				&cmd->redirection[i][j], 1);
		else
			print_error(true, "Permission denied", &cmd->redirection[i][j], 1);
	}
	if (i == last_redir_out(cmd) && \
		(!pipe || (pipe && pipe[0] != -2 && pipe[1] != -2)))
		redir_output(*fd, pipe, cmd);
}

void	do_redirection_one(t_cmd *cmd, int *fd)
{
	size_t	i;
	int		pipe[2];
	int		fd_in;

	i = -1;
	pipe[0] = -2;
	pipe[1] = -2;
	fd_in = 0;
	while (cmd->redirection && cmd->redirection[++i])
	{
		if (cmd->redirection[i][0] == '<')
			do_input(cmd, pipe, i, &fd_in);
		if (cmd->redirection[i][0] == '>')
			do_output(cmd, pipe, i, fd);
	}
}
