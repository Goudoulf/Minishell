/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:44:07 by rjacq             #+#    #+#             */
/*   Updated: 2024/03/08 10:34:25 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	print_error(char *error, char *str)
{
	write(2, str, ft_strlen(str));
	write(2, " :", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

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

static void	dchevron(char *limiter, int *fd)
{
	char	*buf;
	int		pipefd[2];

	pipe(pipefd);
	buf = readline("> ");
	while (buf != NULL)
	{
		if (strncmp(buf, limiter, strlen(limiter)) == 0)
		{
			free(buf);
			break ;
		}
		write(pipefd[1], buf, strlen(buf));
		write(pipefd[1], "\n", 1);
		free(buf);
		buf = readline("> ");
	}
	close(pipefd[1]);
	*fd = pipefd[0];
}

static void	redir_input(int fd, int pipe[2])
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
	if (pipe)
	{
		if (dup2(pipe[1], 1) == -1)
		{
			perror(ft_itoa(fd));
			closepipe(pipe);
			exit(1);
		}
	}
}

static void	redir_output(int fd, int pipe[2])
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
	if (pipe)
	{
		if (dup2(pipe[0], 0) == -1)
		{
			perror(ft_itoa(pipe[0]));
			closepipe(pipe);
			exit(1);
		}
	}
}

static void	do_input(t_cmd *cmd, int pipe[2])
{
	int		i;
	int		j;
	int		fd;

	i = -1;
	fd = 0;
	while (cmd->input_file && cmd->input_file[++i])
	{
		j = ft_isdigit(cmd->input_file[i][0]);
		if (fd != 0)
			close(fd);
		if (ft_strncmp(&cmd->input_file[i][j], "<<", 2) == 0)
			dchevron(&cmd->input_file[i][2 + j], &fd);
		else if (cmd->input_file[i][j] == '<')
			fd = open(&cmd->input_file[i][++j], O_RDONLY);
		if (fd == -1)
			exit((perror(&cmd->input_file[i][j]), 1));
	}
	redir_input(fd, pipe);
}

static void	do_output(t_cmd *cmd, int pipe[2])
{
	int	i;
	int	j;
	int	fd;

	i = -1;
	fd = 1;
	while (cmd->output_file && cmd->output_file[++i])
	{
		j = ft_isdigit(cmd->output_file[i][0]);
		if (fd != 1)
			close(fd);
		if (ft_strncmp(&cmd->output_file[i][j], ">>", 2) == 0)
		{
			fd = open(&cmd->output_file[i][2 + j], O_CREAT | O_WRONLY | O_APPEND, 00644);
			j += 2;
		}
		else if (cmd->output_file[i][j] == '>')
			fd = open(&cmd->output_file[i][++j], O_CREAT | O_WRONLY | O_TRUNC, 00644);
		if (fd == -1)
			exit((perror(&cmd->output_file[i][j]), 1));
	}
	redir_output(fd, pipe);
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

static void	child(t_cmd *cmd, char **envp)
{
	if (cmd->input_file)
		do_input(cmd, NULL);
	if (cmd->output_file)
		do_output(cmd, NULL);
	if (cmd->cmd)
		do_cmd(cmd, envp);
}

static void	last_child(t_cmd *cmd, int pipe[2], char **envp)
{
	if (cmd->output_file)
		do_output(cmd, pipe);
	else
	{
		close(pipe[1]);
		dup2(pipe[0], 0);
		close(pipe[0]);
	}
	if (cmd->cmd)
		do_cmd(cmd, envp);
}

static void	first_child(t_cmd *cmd, int pipe[2], char **envp)
{
	if (cmd->input_file)
		do_input(cmd, pipe);
	else
	{
		close(pipe[0]);
		dup2(pipe[1], 1);
		close(pipe[1]);
	}
	if (cmd->cmd)
		do_cmd(cmd, envp);
}

static void	child_pipe(t_cmd *cmd, int pipe1[2], int pipe2[2], char **envp)
{
	if (cmd->input_file)
		do_input(cmd, pipe2);
	else
	{
		close(pipe2[0]);
		dup2(pipe2[1], 1);
		close(pipe2[1]);
	}
	if (cmd->output_file)
		do_output(cmd, pipe1);
	else
	{
		close(pipe1[1]);
		dup2(pipe1[0], 0);
		close(pipe1[0]);
	}
	if (cmd->cmd)
		do_cmd(cmd, envp);
}

static int	exec_last(t_cmd *cmd, char **envp, int pipe1[2], pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
		return (1);
	if (*pid == 0)
		last_child(cmd, pipe1, envp);
	return (0);
}

static int	for_eachpipe(t_cmd *cmd, char **envp, int pipe1[2], pid_t *pid)
{
	int	pipe2[2];
	size_t	i;

	i = 1;
	while (cmd)
	{
		if (!cmd->next)
			return (exec_last(cmd, envp, pipe1, &pid[i]));
		else
		{
			if (pipe(pipe2) == -1)
				return (1);
			pid[i] = fork();
			if (pid[i] == -1)
				return (1);
			if (pid[i] == 0)
				child_pipe(cmd, pipe1, pipe2, envp);
			else
			{
				closepipe(pipe1);
				pipe1[0] = pipe2[0];
				pipe1[1] = pipe2[1];
			}
		}
		cmd = cmd->next;
		i++;
	}
	return (0);
}

static int	exec_pipe(t_cmd *cmd, char **envp, pid_t *pid, int pipe1[2])
{
	if (pipe(pipe1) == -1)
		return (1);
	pid[0] = fork();
	if (pid[0] == -1)
		return (1);
	if (pid[0] == 0)
		first_child(cmd, pipe1, envp);
	cmd = cmd->next;
	for_eachpipe(cmd, envp, pipe1, pid);
	closepipe(pipe1);
	return (0);
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

int	exec_line(t_cmd *cmd, char **envp)
{
	int		pipe1[2];
	int		status;
	int		nbchild;
	int		i;
	pid_t	*pid;

	nbchild = count_child(cmd);
	pid = malloc(sizeof (pid_t) * nbchild);
	if (!cmd->next)
	{
		if (!pid)
			return (1);
		pid[0] = fork();
		if (pid[0] == -1)
			return (1);
		if (pid[0] == 0)
			child(cmd, envp);
	}
	else
		exec_pipe(cmd, envp, pid, pipe1);
	i = -1;
	while (++i < nbchild)
		waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
