/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:15:38 by cassie            #+#    #+#             */
/*   Updated: 2024/03/08 12:01:47 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/includes/libft.h"
# include "../lib/ft_printf/includes/ft_printf.h"

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_list
{
	char			*string;
	char			*var;
	char			*var_content;
	int				isprint;
	struct s_list	*next;
}				t_list;

typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	char			**redirection;
	char			**here_doc;
	pid_t			pid;
	int				pipe_dchevron[2];
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_error
{
	unsigned int	code;
	bool			do_exit;
}				t_error;

// core
void	check_cmd(char *input, t_list **env, t_cmd **cmd, t_error *err);

// builtins
int	ft_echo(char **cmd, t_list **env);
int	ft_pwd(void);
int	ft_export(t_list **env, char **cmd);
int	ft_unset(t_list **env, char **cmd);
void	ft_exit(char **cmd, t_error *err);
int	ft_cd(char **cmd, t_list **env);

// init

void	init_all(t_cmd **cmd, t_list **env, t_error *err, char **envp);
void	inc_shell_lvl(t_list **env);

// utils

char *ft_strtok(char *string, char *delim);
char *ft_strtok_quote(char *string, char *delim);
size_t infile_count(char *line);
size_t outfile_count(char *line);
int	ft_is_chevron(int c);

// signal

void signal_handling();

// list

t_list	*ft_lst_new(char *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lst_print(t_list **list);
void	ft_lstclear(t_list **lst);
void	ft_cmdclear(t_cmd **cmd);
void	ft_cmd_print(t_cmd **cmd);
t_list	*get_next_min(t_list **stack);
void	ft_lst_set_isprint(t_list **lst);

// parsing

void	line_parsing(t_cmd **cmd, char *line, t_list **env, t_error *err);
char	*clean_line(char *line);
int	check_line_error(char *line);
char	*add_space_chevron(char *line);
char	*check_dollars(char *line, t_list **env, t_error *err);
char	**split_pipe(char *line);
void	line_to_cmd(t_cmd **cmd, char *line, t_list **env);
void clean_quote(t_cmd **cmd);
void	clean_redirection(t_cmd **cmd);

size_t	cmd_count(char *s, char c);
size_t infile_count(char *line);
size_t outfile_count(char *line);
char	*get_value(t_list **env, char *s);

// exec

int	exec_line(t_cmd *cmd, char **envp);
char	*ft_join(const char *s1, const char *s2);
char	*find_path(char *cmd, char *path);

#endif
