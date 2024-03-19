/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:48:36 by rjacq             #+#    #+#             */
/*   Updated: 2024/03/19 17:20:09 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		return (true);
	if (!ft_strncmp(cmd[0], "pwd", 4))
		return (true);
	if (!ft_strncmp(cmd[0], "cd", 3))
		return (true);
	if (!ft_strncmp(cmd[0], "exit", 5))
		return (true);
	if (!ft_strncmp(cmd[0], "unset", 6))
		return (true);
	if (!ft_strncmp(cmd[0], "export", 7))
		return (true);
	if (!ft_strncmp(cmd[0], "env", 4))
		return (true);
	return (false);
}

void	exec_builtin(char **cmd, t_list **list, t_error *err, int fd)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		ft_echo(cmd, err, fd, true);
	if (!ft_strncmp(cmd[0], "pwd", 4))
		ft_pwd(err, fd, 10, 1);
	if (!ft_strncmp(cmd[0], "cd", 3))
		ft_cd(cmd, list, err);
	if (!ft_strncmp(cmd[0], "exit", 5))
		ft_exit(cmd, err, 0);
	if (!ft_strncmp(cmd[0], "unset", 6))
		ft_unset(list, cmd, err, -1);
	if (!ft_strncmp(cmd[0], "export", 7))
		ft_export(list, cmd, err, fd);
	if (!ft_strncmp(cmd[0], "env", 4))
		ft_lst_print(list, err, fd);
}

bool	check_builtin(char **cmd, t_list **list, t_error *err)
{
	int	fd[2];

	fd[0] = 0;
	fd[1] = 1;
	if (is_builtin(cmd) == false)
		return (false);
	else
		exec_builtin(cmd, list, err, 1);
	closepipe(fd);
	exit(err->code);
}

static void	path_null_error(t_cmd *cmd)
{
	if (ft_strncmp(".", cmd->cmd[0], 2) == 0 || \
		ft_strncmp("..", cmd->cmd[0], 3) == 0)
		print_error(false, "Command not found", cmd->cmd[0], 127);
	if (ft_strncmp("./", cmd->cmd[0], 3) == 0)
		print_error(true, "Is a directory", cmd->cmd[0], 126);
	if (access(cmd->cmd[0], F_OK) == 0) 
		print_error(true, "Permission denied", cmd->cmd[0], 126);
	else
		print_error(true, "No such file or directory", cmd->cmd[0], 127);
}

void	do_cmd(t_cmd *cmd, t_list **lst, t_error *err)
{
	char	**envp;

	if (!check_builtin(cmd->cmd, lst, err))
	{
		envp = ft_lst_to_tab(lst, 0);
		if (cmd->path)
			execve(cmd->path, cmd->cmd, envp);
		free_tab(envp);
	}
	if (get_value(lst, "PATH") == NULL)
		path_null_error(cmd);
	else if (ft_strncmp(".", cmd->cmd[0], 2) == 0 || \
		ft_strncmp("..", cmd->cmd[0], 3) == 0)
		print_error(false, "Command not found", cmd->cmd[0], 127);
	else if (ft_strncmp("./", cmd->cmd[0], 1) == 0 && \
		ft_strncmp("./", cmd->cmd[0], 2) && access(cmd->cmd[0], F_OK) == 0)
		print_error(true, "Permission denied", cmd->cmd[0], 126);
	else if (isdirectory(cmd->cmd[0]) && access(cmd->path, F_OK) == -1)
		print_error(true, "No such file or directory", cmd->cmd[0], 127);
	else if (cmd->path && isdirectory(cmd->path) && cmd->cmd[0][0])
		print_error(true, "Is a directory", cmd->cmd[0], 126);
	else
		print_error(false, "Command not found", cmd->cmd[0], 127);
}
