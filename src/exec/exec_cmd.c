/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq < rjacq@student.42lyon.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:44:07 by rjacq             #+#    #+#             */
/*   Updated: 2024/03/19 14:43:42 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_one(t_cmd *cmd, t_list **lst, t_error *err)
{
	int	fd;

	if (for_each_here_doc(cmd, lst, err) == -1)
		return (-1);
	if (cmd->cmd && is_builtin(cmd->cmd))
	{
		fd = 1;
		if (cmd->redirection)
			do_redirection_one(cmd, &fd);
		exec_builtin(cmd->cmd, lst, err, fd);
		if (fd != 1)
			if (close(fd) != 0)
				perror(ft_itoa(fd));
		return (err->code);
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (-1);
	if (cmd->pid == 0)
		child(cmd, lst, err);
	if (is_here_doc(cmd))
		closepipe(cmd->pipe_dchevron);
	return (0);
}

int	exec(t_cmd *cmd, t_list **lst, t_error *err)
{
	int	return_value;

	if (!cmd->next)
	{
		return_value = exec_one(cmd, lst, err);
		return (return_value);
	}
	else
	{
		return_value = exec_pipe(cmd, lst, err);
		return (return_value);
	}
}

int	exec_line(t_cmd *cmd, t_list **lst, t_error *err)
{
	int		status;
	int		last_status;
	int		ret_value;
	pid_t	wpid;

	status = 0;
	wpid = 0;
	ret_value = exec(cmd, lst, err);
	if (ret_value == -1)
		return (1);
	else if (ret_value != 0)
		return (ret_value);
	while (cmd->next)
		cmd = cmd->next;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(0, &status, 0);
		if (wpid == cmd->pid)
			last_status = status;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
