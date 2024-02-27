/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:44:07 by rjacq             #+#    #+#             */
/*   Updated: 2024/02/27 16:04:42 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int    isdirectory(char *str)
{
    size_t    i;

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

static void	dchevron(char *str, int *fd)
{
	char	*buf;

	*fd = open("tmp", O_CREAT | O_RDWR);
	buf = readline(">");
	write(*fd, buf, ft_strlen(buf));
	while (ft_strncmp(buf, str, ft_strlen(str)) != 0)
	{
		free(buf);
		buf = readline(">");
		write(*fd, buf, ft_strlen(buf));
	}
}

static void	redir_input(int fd, int pipe[2], int redir)
{
	if (dup2(fd, redir) == -1)
	{
		perror(ft_itoa(fd));
		closepipe(pipe);
		exit(1);
	}
	if (close(fd) == -1)
		perror(ft_itoa(fd));
	if (dup2(pipe[1], 1) == -1)
	{
		perror(ft_itoa(fd));
		closepipe(pipe);
		exit(1);
	}
}

static void	do_input(t_cmd *cmd, int pipe[2])
{
	int		i;
	int		j;
	int		fd;
	int		redir;

	i = 0;
	while (cmd->input_file[i])
	{
		j = ft_isdigit(cmd->input_file[i][0]);
		redir = ((j == 1) * ft_atoi(cmd->input_file[i])) + ((j == 0) * 0);
		if (ft_strncmp(&cmd->input_file[i][j], "<<", 2) == 0)
			dchevron(&cmd->input_file[i][2 + j], &fd);
		else if (cmd->input_file[i][j] == '<')
			fd = open(&cmd->input_file[i][1 + j], O_RDONLY);
		if (fd == -1)
		{
			perror(&cmd->input_file[i][j]);
			//print_error(strerror(errno), &cmd->input_file[i][j]);
			closepipe(pipe);
			exit(1);
		}
		i++;
	}
	redir_input(fd, pipe, redir);
}

static void	redir_output(int fd, int pipe[2], int redir)
{
	if (dup2(fd, redir) == -1)
	{
		perror(ft_itoa(fd));
		closepipe(pipe);
		exit(1);
	}
	if (close(fd) == -1)
		perror(ft_itoa(fd));
	if (dup2(pipe[0], 0) == -1)
	{
		perror(ft_itoa(pipe[0])); //fd / pipe
		closepipe(pipe);
		exit(1);
	}
}

static void	do_output(t_cmd *cmd, int pipe[2])
{
	int	i;
	int	j;
	int	redir;
	int	fd;

	i = 0;
	while (cmd->output_file[i])
	{
		j = ft_isdigit(cmd->output_file[i][0]);
		redir = ((j == 1) * ft_atoi(cmd->output_file[i])) + ((j == 0) * 1);
		if (ft_strncmp(&cmd->output_file[i][j], ">>", 2) == 0)
		{
			fd = open(&cmd->output_file[i][2 + j], O_CREAT | O_WRONLY | O_APPEND, 00644);
			j += 2;
		}
		else if (cmd->output_file[i][j] == '>')
		{
			fd = open(&cmd->output_file[i][1 + j], O_CREAT | O_WRONLY | O_TRUNC, 00644);
			j += 1;
		}
		if (fd == -1)
		{
			perror(&cmd->input_file[i][j]);
			//print_error(strerror(errno), &cmd->input_file[i][j]);
			closepipe(pipe);
			exit(1);
		}
		i++;
	}
	redir_output(fd, pipe, redir);
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

static void	child(t_cmd *cmd, int pipe[2], char **envp)
{
	if (cmd->input_file)
		do_input(cmd, pipe);
	if (cmd->output_file)
		do_output(cmd, pipe);
	closepipe(pipe);
	if (cmd->cmd)
		do_cmd(cmd, envp);
}

int	exec_line(t_cmd *cmd, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) == -1)
		exit(1);
	while (cmd)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			child(cmd, fd, envp);
		cmd = cmd->next;
	}
	closepipe(fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return(WEXITSTATUS(status));
	return(0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char *cmd1[] = {"cat", NULL};
// 	char *path1 = "/usr/bin/cat";
// 	char *in1[] = {"<in", NULL};
// 	char **out1 = NULL;
// 	char *cmd2[] = {"cat", NULL};
// 	char *path2 = "/usr/bin/cat";
// 	char **in2 = NULL;
// 	char *out2[] = {">out", NULL};
// 	t_cmd block1;
// 	t_cmd block2;
// 	char	**env;

// 	block1.cmd = cmd1;
// 	block2.cmd = cmd2;
// 	block1.next = &block2;
// 	block2.next = NULL;
// 	block1.input_file = in1;
// 	block2.input_file = in2;
// 	block1.output_file = out1;
// 	block2.output_file = out2;
// 	block1.path = path1;
// 	block2.path = path2;
// 	exec_line(&block1, envp);
// }
