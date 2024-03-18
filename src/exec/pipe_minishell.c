/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq < rjacq@student.42lyon.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:44:07 by rjacq             #+#    #+#             */
/*   Updated: 2024/03/18 13:36:00 by rjacq            ###   ########.fr       */
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

static void	closepipe(int pipe[2])
{
	if (close(pipe[0]) == -1)
		perror(ft_itoa(pipe[0]));
	if (close(pipe[1]) == -1)
		perror(ft_itoa(pipe[1]));
}

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

static void	print_error(char *error, char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

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

static void	do_input2(t_cmd *cmd, int i)
{
	int		fd;

	fd = 0;
	if (ft_strncmp(cmd->redirection[i], "<<", 2) == 0)
	{
		if (close(cmd->pipe_dchevron[1]) == -1)
			perror(ft_itoa(cmd->pipe_dchevron[1]));
		fd = cmd->pipe_dchevron[0];
	}
	else if (cmd->redirection[i][0] == '<')
		fd = open(&cmd->redirection[i][1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		if (errno == 2)
			print_error("No such file or directory", &cmd->redirection[i][1]);
		else	
			print_error("Permission denied", &cmd->redirection[i][1]);
		exit(1);
	}
}

static void	do_input(t_cmd *cmd, int pipe[2], size_t i, int fd[2])
{
	if (fd[0] != 0)
		if (close(fd[0]) == -1)
			perror(ft_itoa(fd[0]));
	if (ft_strncmp(cmd->redirection[i], "<<", 2) == 0)
	{
		if (close(cmd->pipe_dchevron[1]) == -1)
			perror(ft_itoa(cmd->pipe_dchevron[1]));
		fd[0] = cmd->pipe_dchevron[0];
	}
	else if (cmd->redirection[i][0] == '<')
		fd[0] = open(&cmd->redirection[i][1], O_RDONLY);
	if (fd[0] == -1)
	{
		write(2, "minishell: ", 11);
		if (errno == 2)
			print_error("No such file or directory", &cmd->redirection[i][1]);
		else	
			print_error("Permission denied", &cmd->redirection[i][1]);
		exit(1);
	}
	if (i == last_redir_in(cmd))
		redir_input(fd[0], pipe, cmd);
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

static void	do_output2(t_cmd *cmd, int i, int *fd)
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
		write(2, "minishell: ", 11);
		if (errno == 2)
			print_error("No such file or directory", &cmd->redirection[i][j]);
		else	
			print_error("Permission denied", &cmd->redirection[i][j]);
		exit(1);
	}
}

static void	do_output(t_cmd *cmd, int pipe[2], size_t i, int fd[2])
{
	int	j;

	j = 1;
	if (fd[1] != 1)
		if (close(fd[1]) == -1)
			perror(ft_itoa(fd[1]));
	if (ft_strncmp(cmd->redirection[i], ">>", 2) == 0)
		fd[1] = open(&cmd->redirection[i][++j], O_CREAT | O_RDWR | \
			O_APPEND, 00644);
	else if (cmd->redirection[i][0] == '>')
		fd[1] = open(&cmd->redirection[i][j], O_CREAT | O_RDWR | \
			O_TRUNC, 00644);
	if (fd[1] == -1)
	{
		write(2, "minishell: ", 11);
		if (errno == 2)
			print_error("No such file or directory", &cmd->redirection[i][j]);
		else	
			print_error("Permission denied", &cmd->redirection[i][j]);
		exit(1);
	}
	if (i == last_redir_out(cmd))
		redir_output(fd[1], pipe, cmd);
}

static void	do_redirection_one(t_cmd *cmd, int *fd)
{
	size_t	i;

	i = -1;
	while (cmd->redirection && cmd->redirection[++i])
	{
		if (cmd->redirection[i][0] == '<')
			do_input2(cmd, i);
		if (cmd->redirection[i][0] == '>')
			do_output2(cmd, i, fd);
	}
}

bool	is_builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		return (true);
	if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
		return (true);
	if (!ft_strncmp(cmd->cmd[0], "cd", 3))
		return (true);
	if (!ft_strncmp(cmd->cmd[0], "exit", 5))
		return (true);
	if (!ft_strncmp(cmd->cmd[0], "unset", 6))
		return (true);
	if (!ft_strncmp(cmd->cmd[0], "export", 7))
		return (true);
	if (!ft_strncmp(cmd->cmd[0], "env", 4))
		return (true);
	return (false);
}

void	exec_builtin_one(char	**cmd, t_list **list, t_error *err, int fd)
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

bool	exec_builtin(char	**cmd, t_list **list, t_error *err)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
	{
		ft_echo(cmd, err, 1, true);
		close((close(1), 0));
		exit(err->code);
	}
	if (!ft_strncmp(cmd[0], "pwd", 4))
	{
		ft_pwd(err, 1, 10, 1);
		close((close(1), 0));
		exit(err->code);
	}
	if (!ft_strncmp(cmd[0], "cd", 3))
	{
		ft_cd(cmd, list, err);
		close((close(1), 0));
		exit(err->code);
	}
	if (!ft_strncmp(cmd[0], "exit", 5))
	{
		ft_exit(cmd, err, 0);
		close((close(1), 0));
		exit(err->code);
	}
	if (!ft_strncmp(cmd[0], "unset", 6))
	{
		ft_unset(list, cmd, err, -1);
		close((close(1), 0));
		exit(err->code);
	}
	if (!ft_strncmp(cmd[0], "export", 7))
	{
		ft_export(list, cmd, err, 1);
		close((close(1), 0));
		exit(err->code);
	}
	if (!ft_strncmp(cmd[0], "env", 4))
	{
		ft_lst_print(list, err, 1);
		close((close(1), 0));
		exit(err->code);
	}
	return (false);
}

static void	do_cmd(t_cmd *cmd, t_list **lst, t_error *err)
{
	char	**envp;

	if (!exec_builtin(cmd->cmd, lst, err))
	{
		envp = ft_lst_to_tab(lst, 0);
		if (cmd->path)
			execve(cmd->path, cmd->cmd, envp);
		free_tab(envp);
	}
	if (get_value(lst, "PATH") == NULL)
	{
		if (ft_strncmp(".", cmd->cmd[0], 2) == 0 || \
			ft_strncmp("..", cmd->cmd[0], 3) == 0)
		{
			print_error("Command not found", cmd->cmd[0]);
			exit(127);
		}
		write(2, "minishell: ", 11);
		if (ft_strncmp("./", cmd->cmd[0], 3) == 0)
			print_error("Is a directory", cmd->cmd[0]);
		else
			perror(cmd->cmd[0]);
		exit(126);
	}
	else if (ft_strncmp(".", cmd->cmd[0], 2) == 0 || \
		ft_strncmp("..", cmd->cmd[0], 3) == 0)
	{
		print_error("Command not found", cmd->cmd[0]);
		exit(127);
	}
	else if (ft_strncmp("./", cmd->cmd[0], 1) == 0 && \
		ft_strncmp("./", cmd->cmd[0], 3) && access(cmd->cmd[0], F_OK) == 0)
	{
		write(2, "minishell: ", 11);
		print_error("Permission denied", cmd->cmd[0]);
		exit(126);
	}
	else if (cmd->cmd[0] && isdirectory(cmd->cmd[0]) && \
		access(cmd->path, F_OK) == -1)
	{
		write(2, "minishell: ", 11);
		print_error("No such file or directory", cmd->cmd[0]);
		exit(127);
	}
	else if (cmd->path && isdirectory(cmd->path) && cmd->cmd[0][0])
	{
		write(2, "minishell: ", 11);
		print_error("Is a directory", cmd->cmd[0]);
		exit(126);
	}
	else
		print_error("Command not found", cmd->cmd[0]);
	exit((close(0), close(1), 127));
}

static void	do_redirection(t_cmd *cmd, int pipe1[2], int pipe2[2], int child)
{
	size_t	i;
	int		fd[2];

	i = -1;
	fd[0] = 0;
	fd[1] = 1;
	while (cmd->redirection && cmd->redirection[++i])
	{
		if (child == 0)
		{
			if (cmd->redirection[i][0] == '<')
				do_input(cmd, pipe1, i, fd);
			if (cmd->redirection[i][0] == '>')
				do_output(cmd, pipe1, i, fd);
		}
		else if (child == 1)
		{
			if (cmd->redirection[i][0] == '<')
				do_input(cmd, pipe1, i, fd);
			if (cmd->redirection[i][0] == '>')
				do_output(cmd, pipe1, i, fd);
		}
		else if (child == 2)
		{
			if (cmd->redirection[i][0] == '<')
				do_input(cmd, pipe2, i, fd);
			if (cmd->redirection[i][0] == '>')
				do_output(cmd, pipe1, i, fd);
		}
		else if (child == 3)
		{
			if (cmd->redirection[i][0] == '<')
				do_input(cmd, pipe2, i, fd);
			if (cmd->redirection[i][0] == '>')
				do_output(cmd, pipe1, i, fd);
		}
	}
	if (child == 1 && !has_redir_in(cmd))
	{
		close(pipe1[0]);
		dup2(pipe1[1], 1);
		close(pipe1[1]);
	}
	if (child == 2 && !has_redir_in(cmd))
	{
		close(pipe2[0]);
		dup2(pipe2[1], 1);
		close(pipe2[1]);
	}
	if ((child == 2 || child == 3) && !has_redir_in(cmd) && !has_redir_out(cmd))
	{
		close(pipe1[1]);
		dup2(pipe1[0], 0);
		close(pipe1[0]);
	}
}

static void	child(t_cmd *cmd, t_list **lst, t_error *err)
{
	do_redirection(cmd, NULL, NULL, 0);
	if (cmd->cmd)
		do_cmd(cmd, lst, err);
	exit (0);
}

static void	last_child(t_cmd *cmd, int pipe[2], t_list **lst, t_error *err)
{
	do_redirection(cmd, pipe, NULL, 3);
	if (cmd->cmd)
		do_cmd(cmd, lst, err);
	exit (0);
}

static void	first_child(t_cmd *cmd, int pipe[2], t_list **lst, t_error *err)
{
	do_redirection(cmd, pipe, NULL, 1);
	if (cmd->cmd)
		do_cmd(cmd, lst, err);
	exit (0);
}

static void	child_pipe(t_cmd *cmd, int pipefd[2][2], t_list **lst, t_error *err)
{
	do_redirection(cmd, pipefd[0], pipefd[1], 2);
	if (cmd->cmd)
		do_cmd(cmd, lst, err);
	exit (0);
}

static int	exec_last(t_cmd *cmd, t_list **lst, int pipe1[2], t_error *err)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
		last_child(cmd, pipe1, lst, err);
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

static void	do_here_doc(char *limiter, int pipefd[2], t_list **env, t_error *err)
{
	char	*buf;
	size_t	size;
	
	buf = readline("> ");
	if (buf == NULL)
		return ((void)write(2, "minishell: warning: here-document delimited by \
			end-of-file (wanted `stop')\n", 75));
	size = ft_strlen(limiter) + 1;
	while (ft_strncmp(buf, limiter, size))
	{
		buf = check_dollars(buf, env, err);
		write(pipefd[1], buf, ft_strlen(buf));
		write(pipefd[1], "\n", 1);
		free(buf);
		buf = readline("> ");
		if (buf == NULL)
			return ((void)write(2, "minishell: warning: here-document \
				delimited by end-of-file (wanted `stop')\n", 75));
	}
	free(buf);
}

void	for_each_here_doc(t_cmd *cmd, t_list **env, t_error *err)
{
	size_t	i;
	bool	first;

	while (cmd)
	{
		first = true;
		i = -1;
		while (cmd->here_doc && cmd->here_doc[++i])
		{
			if (first == false)
				closepipe(cmd->pipe_dchevron);
			first = false;
			pipe(cmd->pipe_dchevron);
			do_here_doc(&cmd->here_doc[i][2], cmd->pipe_dchevron, env, err);
		}
		cmd = cmd->next;
	}
}

static int	exec_pipe(t_cmd *cmd, t_list **lst, t_error *err)
{
	int	pipe_tab[2][2];

	for_each_here_doc(cmd, lst, err);
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

int	exec_one(t_cmd *cmd, t_list **lst, t_error *err)
{
	int fd;
	
	for_each_here_doc(cmd, lst, err);
	//signal_handling_child();
	if (cmd->cmd && is_builtin(cmd))
	{
		fd = 1;
		if (cmd->redirection)
			do_redirection_one(cmd, &fd);
		exec_builtin_one(cmd->cmd, lst, err, fd);
		if (fd != 1)
			close(fd);
		return(err->code);
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
		child(cmd, lst, err);
	if (is_here_doc(cmd))
		closepipe(cmd->pipe_dchevron);
	return (0);
}

int	exec_line(t_cmd *cmd, t_list **lst, t_error *err)
{
	int		status;
	int		last_status;
	pid_t	wpid;

	status = 0;
	wpid = 0;
	if (!cmd->next)
	{
		if (exec_one(cmd, lst, err) != 0)
			return (err->code);
	}
	else
	{
		if (exec_pipe(cmd, lst, err) != 0)
			return (err->code);
	}
	while (cmd->next)
		cmd = cmd->next;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(0, &status, 0);
		if (wpid == cmd->pid)
			last_status = status;
		continue ;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
