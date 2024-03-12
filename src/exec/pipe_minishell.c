/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:44:07 by rjacq             #+#    #+#             */
/*   Updated: 2024/03/12 17:10:50 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// static int	ft_lstsize(t_list **lst)
// {
// 	int	lsize;

// 	lsize = 0;
// 	while (lst != NULL && *lst != NULL)
// 	{
// 		(*lst) = (*lst)->next;
// 		lsize++;
// 	}
// 	return (lsize);
// }

// static char	**lst_to_tab(t_list **lst)
// {
// 	int		i;
// 	int		j;
// 	int		lstsize;
// 	int		strsize;
// 	char	**tab;

// 	i = -1;
// 	lstsize = ft_lstsize(lst);
// 	tab = malloc(sizeof (char *) * lstsize + 1);
// 	if (!tab)
// 		return NULL;
// 	tab[lstsize] = NULL;
// 	while (i++ < lstsize)
// 	{
// 		j = -1;
// 		strsize = ft_strlen((*lst)->string);
// 		tab[i] = malloc (sizeof (char) * strsize + 1);
// 		tab[i][strsize] = 0;
// 		while (j++ < strsize)
// 			tab[i][j] = (*lst)->string[j];
// 		(*lst) = (*lst)->next;
// 	}
// 	return (tab);
// }

/*char	*ft_realloc(char *str, char *buf)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	strlen;
	size_t	buflen;

	i = -1;
	strlen = ft_strlen(str);
	buflen = ft_strlen(buf);
	new_str = malloc(sizeof(char) * strlen + buflen + 1);
	new_str[strlen + buflen] = 0;
	while (++i < strlen)
		new_str[i] = str[i];
	free(str);
	j = -1;
	while (++j < buflen)
		new_str[i + j] = buf[j];
	free(buf);
	return (new_str);
}*/

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

static int	isdirectory(char *str)
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

bool	is_dechevron(t_cmd *cmd)
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
	if ((pipe && !is_dechevron(cmd) && !has_redir_out(cmd)) || cmd->next)
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

static void	do_input(t_cmd *cmd, int pipe[2], int i)
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
		exit((perror(ft_itoa(fd)), 1));
	redir_input(fd, pipe, cmd);
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

static void	do_output(t_cmd *cmd, int pipe[2], int i)
{
	int	fd;

	fd = 1;
	if (fd != 1)
		if (close(fd) == -1)
			perror(ft_itoa(fd));
	if (ft_strncmp(cmd->redirection[i], ">>", 2) == 0)
		fd = open(&cmd->redirection[i][2], O_CREAT | O_WRONLY | O_APPEND, 00644);
	else if (cmd->redirection[i][0] == '>')
		fd = open(&cmd->redirection[i][1], O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd == -1)
		exit((perror(ft_itoa(fd)), 1));
	redir_output(fd, pipe, cmd);
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

void	exec_builtin2(char	**cmd, t_list **list, t_error *err)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		ft_echo(cmd);
	if (!ft_strncmp(cmd[0], "pwd", 4))
		ft_pwd(cmd);
	if (!ft_strncmp(cmd[0], "cd", 3))
		ft_cd(cmd, list, err);
	if (!ft_strncmp(cmd[0], "exit", 5))
		ft_exit(cmd, err);
	if (!ft_strncmp(cmd[0], "unset", 6))
		ft_unset(list, cmd, err);
	if (!ft_strncmp(cmd[0], "export", 7))
		ft_export(list, cmd, err);
	if (!ft_strncmp(cmd[0], "env", 4))
		ft_lst_print(list);
}

bool	exec_builtin(char	**cmd, t_list **list, t_error *err)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
	{
		ft_echo(cmd);
		close((close(1), 0));
		exit(err->code);
	}
	if (!ft_strncmp(cmd[0], "pwd", 4))
	{
		ft_pwd(cmd);
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
		ft_exit(cmd, err);
		close((close(1), 0));
		exit(err->code);
	}
	if (!ft_strncmp(cmd[0], "unset", 6))
	{
		ft_unset(list, cmd, err);
		close((close(1), 0));
		exit(err->code);
	}
	if (!ft_strncmp(cmd[0], "export", 7))
	{
		ft_export(list, cmd, err);
		close((close(1), 0));
		exit(err->code);
	}
	if (!ft_strncmp(cmd[0], "env", 4))
	{
		ft_lst_print(list);
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
		envp = ft_lst_to_tab(lst);
		if (cmd->path)
			execve(cmd->path, cmd->cmd, envp);
		free_tab(envp);
	}
	if (cmd->path && isdirectory(cmd->path) && cmd->cmd[0][0])
	{
		write(2, "minishell: ", 11);
		print_error("Is a directory", cmd->cmd[0]);
	}
	else if (cmd->cmd[0] && isdirectory(cmd->cmd[0]))
	{
		write(2, "minishell: ", 11);
		print_error("No such file or directory", cmd->cmd[0]);
	}
	else
		print_error("Command not found", cmd->cmd[0]);
	if (cmd->path && isdirectory(cmd->path) && cmd->cmd[0] && cmd->cmd[0][0])
		exit((close(0), close(1), 126));
	exit((close(0), close(1), 127));
}

static void	do_redirection(t_cmd *cmd, int pipe1[2], int pipe2[2], int child)
{
	size_t	i;

	i = -1;
	while (cmd->redirection && cmd->redirection[++i])
	{
		if (child == 0)
		{
			if (cmd->redirection[i][0] == '<')
				do_input(cmd, pipe1, i);
			if (cmd->redirection[i][0] == '>')
				do_output(cmd, pipe1, i);
		}
		else if (child == 1)
		{
			if (cmd->redirection[i][0] == '<')
				do_input(cmd, pipe1, i);
			if (cmd->redirection[i][0] == '>')
				do_output(cmd, pipe1, i);
		}
		else if (child == 2)
		{
			if (cmd->redirection[i][0] == '<')
				do_input(cmd, pipe2, i);
			if (cmd->redirection[i][0] == '>')
				do_output(cmd, pipe1, i);
		}
		else if (child == 3)
		{
			if (cmd->redirection[i][0] == '<')
				do_input(cmd, pipe2, i);
			if (cmd->redirection[i][0] == '>')
				do_output(cmd, pipe1, i);
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
	if (cmd->redirection)
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

static void	child_pipe(t_cmd *cmd, int pipe1[2], int pipe2[2], t_list **lst, t_error *err)
{
	do_redirection(cmd, pipe1, pipe2, 2);
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

static int	for_eachpipe(t_cmd *cmd, t_list **lst, int pipe1[2], t_error *err)
{
	int	pipe2[2];
	size_t	i;

	i = 1;
	while (cmd)
	{
		if (!cmd->next)
			exec_last(cmd, lst, pipe1, err);
		else
		{
			if (pipe(pipe2) == -1)
				return (1);
			cmd->pid = fork();
			if (cmd->pid == -1)
				return (1);
			if (cmd->pid == 0)
				child_pipe(cmd, pipe1, pipe2, lst, err);
			else
			{
				closepipe(pipe1);
				pipe1[0] = pipe2[0];
				pipe1[1] = pipe2[1];
			}
		}
		if (is_dechevron(cmd))
			closepipe(cmd->pipe_dchevron);
		cmd = cmd->next;
		i++;
	}
	if (count_child(cmd) > 2)
		closepipe(pipe2);
	return (0);
}

static void	dchevron(char *limiter, int pipefd[2])
{
	char	*buf;
	size_t	size;

	buf = readline("> ");
	size = ft_strlen(buf);
	if (ft_strlen(limiter) > ft_strlen(buf))
		size = ft_strlen(limiter);
	while (ft_strncmp(buf, limiter, size))
	{
		write(pipefd[1], buf, ft_strlen(buf));
		write(pipefd[1], "\n", 1);
		free(buf);
		buf = readline("> ");
	}
	free(buf);
}

void	for_each_dchevron(t_cmd *cmd)
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
			dchevron(&cmd->here_doc[i][2], cmd->pipe_dchevron);
		}
		cmd = cmd->next;
	}
}

static int	exec_pipe(t_cmd *cmd, t_list **lst, t_error *err)
{
	int	pipefd[2];

	for_each_dchevron(cmd);
	if (pipe(pipefd) == -1)
		return (1);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
		first_child(cmd, pipefd, lst, err);
	if (is_dechevron(cmd))
		closepipe(cmd->pipe_dchevron);
	cmd = cmd->next;
	for_eachpipe(cmd, lst, pipefd, err);
	closepipe(pipefd);
	return (0);
}

int	exec_line(t_cmd *cmd, t_list **lst, t_error *err)
{
	int		status;
	int		fd[2];

	status = 0;
	if (!cmd->next)
	{
		for_each_dchevron(cmd);
		if (cmd->cmd && is_builtin(cmd))
		{
			fd[0] = dup(0);
			fd[1] = dup(1);
			if (cmd->redirection)
				do_redirection(cmd, NULL, NULL, 0);
			exec_builtin2(cmd->cmd, lst, err);
			dup2(fd[0], 0);
			dup2(fd[1], 1);
			return (err->code);
		}
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (1);
		if (cmd->pid == 0)
			child(cmd, lst, err);
		if (is_dechevron(cmd))
			closepipe(cmd->pipe_dchevron);
	}
	else
		exec_pipe(cmd, lst, err);
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
