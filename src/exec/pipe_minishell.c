/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq < rjacq@student.42lyon.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:44:07 by rjacq             #+#    #+#             */
/*   Updated: 2024/03/08 11:40:07 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	ft_lstsize(t_list *lst)
{
	int	lsize;

	lsize = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		lsize++;
	}
	return (lsize);
}*/

/*static char	**lst_to_tab(t_list *lst)
{
	int		i;
	int		j;
	int		lstsize;
	int		strsize;
	char	**tab;

	i = -1;
	lstsize = ft_lstsize(lst);
	tab = malloc(sizeof (char *) * lstsize + 1);
	tab[lstsize] = NULL;
	while (i++ < lstsize)
	{
		j = -1;
		strsize = ft_strlen(lst->string);
		tab[i] = malloc (sizeof (char) * strsize + 1);
		tab[i][strsize] = 0;
		while (j++ < strsize)
			tab[i][j] = lst->string[j];
		lst = lst->next;
	}
	return (tab);
}*/

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
	write(2, " :", 2);
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
		close(pipe[0]);
		if (dup2(pipe[1], 1) == -1)
		{
			perror(ft_itoa(fd));
			closepipe(pipe);
			exit(1);
		}
		close(pipe[1]);
	}
}

static void	do_input(t_cmd *cmd, int pipe[2], int i)
{
	int		fd;

	fd = 0;
	if (ft_strncmp(cmd->redirection[i], "<<", 2) == 0)
	{
		close(cmd->pipe_dchevron[1]);
		fd = cmd->pipe_dchevron[0];
	}
	else if (cmd->redirection[i][0] == '<')
	{
		/*if (fd != 0)
			close(fd);*/
		fd = open(&cmd->redirection[i][1], O_RDONLY);
	}
	if (fd == -1)
		exit((perror(&cmd->redirection[i][1]), 1));
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
	if (pipe /*&& !is_dechevron(cmd) */&& !has_redir_in(cmd))
	{
		close(pipe[1]);
		if (dup2(pipe[0], 0) == -1)
		{
			perror(ft_itoa(pipe[0]));
			closepipe(pipe);
			exit(1);
		}
		close(pipe[0]);
	}
}

static void	do_output(t_cmd *cmd, int pipe[2], int i)
{
	int	j;
	int	fd;

	fd = 1;
	j = 0;
	if (fd != 1)
		close(fd);
	if (ft_strncmp(cmd->redirection[i], ">>", 2) == 0)
	{
		j += 2;
		fd = open(&cmd->redirection[i][j], O_CREAT | O_WRONLY | O_APPEND, 00644);
	}
	else if (cmd->redirection[i][0] == '>')
		fd = open(&cmd->redirection[i][++j], O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd == -1)
		exit((perror(&cmd->redirection[i][j]), 1));
	redir_output(fd, pipe, cmd);
}

static void	do_cmd(t_cmd *cmd, char **envp)
{
	execve(cmd->path, cmd->cmd, envp);
	if (!cmd->cmd[0])
		print_error("Execution error", cmd->cmd[0]);
	else if (cmd->cmd[0] && cmd->cmd[0][0] == 0)
		print_error("Permission denied", cmd->cmd[0]);
	else if (cmd->path && isdirectory(cmd->path) && \
		access(cmd->path, F_OK) == -1)
		perror(cmd->cmd[0]);
	else if (errno == 2 || !cmd->path)
		print_error("Command not found", cmd->cmd[0]);
	else
		perror(cmd->cmd[0]);
	if (cmd->cmd[0] && cmd->cmd[0][0] == 0)
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

static void	child(t_cmd *cmd, char **envp)
{
	if (cmd->redirection)
		do_redirection(cmd, NULL, NULL, 0);
	if (cmd->cmd)
		do_cmd(cmd, envp);
}

static void	last_child(t_cmd *cmd, int pipe[2], char **envp)
{
	do_redirection(cmd, pipe, NULL, 3);
	if (cmd->cmd)
		do_cmd(cmd, envp);
}

static void	first_child(t_cmd *cmd, int pipe[2], char **envp)
{
	do_redirection(cmd, pipe, NULL, 1);
	if (cmd->cmd)
		do_cmd(cmd, envp);
}

static void	child_pipe(t_cmd *cmd, int pipe1[2], int pipe2[2], char **envp)
{
	do_redirection(cmd, pipe1, pipe2, 2);
	if (cmd->cmd)
		do_cmd(cmd, envp);
}

static int	exec_last(t_cmd *cmd, char **envp, int pipe1[2])
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
		last_child(cmd, pipe1, envp);
	return (0);
}

static int	for_eachpipe(t_cmd *cmd, char **envp, int pipe1[2])
{
	int	pipe2[2];
	size_t	i;

	i = 1;
	while (cmd)
	{
		if (!cmd->next)
			exec_last(cmd, envp, pipe1);
		else
		{
			if (pipe(pipe2) == -1)
				return (1);
			cmd->pid = fork();
			if (cmd->pid == -1)
				return (1);
			if (cmd->pid == 0)
				child_pipe(cmd, pipe1, pipe2, envp);
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
	size_t	count;

	while (cmd)
	{
		//pipe(cmd->pipe_dchevron);
		count = 0;
		i = -1;
		while (cmd->redirection && cmd->redirection[++i])
		{
			if (ft_strncmp(cmd->redirection[i], "<<", 2) == 0)
			{
				if (count++ > 0)
					closepipe(cmd->pipe_dchevron);
				pipe(cmd->pipe_dchevron);
				dchevron(&cmd->redirection[i][2], cmd->pipe_dchevron);
			}
		}
		cmd = cmd->next;
	}
}

static int	exec_pipe(t_cmd *cmd, char **envp)
{
	int	pipefd[2];

	for_each_dchevron(cmd);
	if (pipe(pipefd) == -1)
		return (1);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
		first_child(cmd, pipefd, envp);
	if (is_dechevron(cmd))
		closepipe(cmd->pipe_dchevron);
	cmd = cmd->next;
	for_eachpipe(cmd, envp, pipefd);
	closepipe(pipefd);
	return (0);
}

int	exec_line(t_cmd *cmd, char **envp)
{
	int		status;

	if (!cmd->next)
	{
		for_each_dchevron(cmd);
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (1);
		if (cmd->pid == 0)
			child(cmd, envp);
		if (is_dechevron(cmd))
			closepipe(cmd->pipe_dchevron);
	}
	else
		exec_pipe(cmd, envp);
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
