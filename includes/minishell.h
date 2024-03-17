/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:15:38 by cassie            #+#    #+#             */
/*   Updated: 2024/03/17 13:01:25 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/includes/libft.h"
# include "../lib/gnl/get_next_line.h"
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
# include <stddef.h>

typedef struct s_list
{
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
int		ft_echo(char **cmd, t_error *err, int fd, bool new_line);
int		ft_pwd(t_error *err, int fd, int size, int i);
int		ft_export(t_list **env, char **cmd, t_error *err, int fd);
int		ft_unset(t_list **env, char **cmd, t_error *err, int i);
void	ft_exit(char **cmd, t_error *err, unsigned char code);
int		ft_cd(char **cmd, t_list **env, t_error *err);
char	*ft_pwd2(int size, int i);

// init

void	init_all(t_cmd **cmd, t_list **env, t_error *err, char **envp);
void	inc_shell_lvl(t_list **env);

// utils

char	*ft_strtok_quote(char *string, char *delim);
void	quote_mode(char *c_quote, char char_line);
size_t	infile_count(char *line);
size_t	outfile_count(char *line);
int		ft_is_chevron(int c);
int		ft_is_space(int c);
int		ft_is_end(int c);
char	**create_tab(size_t nelem);
void	free_tab(char **tab);
size_t	tab_size(char **cmd);

// signal

void	signal_handling(void);
void	signal_handling_child(void);
void	signal_handling_hd(void);
void	sigint_handler(int sig);
void	sigint_handler_hd(int sig);

// list

t_list	*ft_lst_new(char *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lst_print(t_list **list, t_error *err, int fd);
void	ft_lstclear(t_list **lst);
t_list	*get_next_min(t_list **stack);
void	ft_lst_set_isprint(t_list **lst);
char	**ft_lst_to_tab(t_list **list, int i);
char	*str_to_char(char *str);
char	*str_from_char(char *str);

// cmd

t_cmd	*ft_cmd_new(char **redirection);
void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new);
t_list	*check_cmd_env(char *arg, t_list **env);
void	ft_cmdclear(t_cmd **cmd);
void	ft_cmd_print(t_cmd **cmd);

// parsing

void	line_parsing(t_cmd **cmd, char *line, t_list **env, t_error *err);
char	*del_space_chevron(char *line);
int		check_line_error(char *line, t_error *err);
char	*add_space_chevron(char *line);
char	*check_dollars(char *line, t_list **env, t_error *err);
char	*replace_dollar(char *line, t_list **env, int start, t_error *err);
int		start_dollar(char *line, int dollar_num);
char	**split_pipe(char *line);
char	*line_to_cmd(t_cmd **cmd, char *line);
void	line_to_cmd2(t_cmd **cmd, char *line);
void	clean_quote(t_cmd **cmd);
void	clean_redirection(t_cmd **cmd);
int		start_tilde(char *line, int tilde_num);
char	*check_tilde(char *line, t_list **env);
char	*replace_tilde(char *line, t_list **env, int start);
void	set_quote(bool *quote, char *c_quote, char char_line);

size_t	cmd_count(char *s);
size_t	in_count(char *line);
size_t	out_count(char *line);
char	*get_value(t_list **env, char *s);
void	cmd_add_path(t_cmd **cmd, t_list **env);
int		isdirectory(char *str);
int		stderr_c(const char *str1, const char c, const char *str3, int ret);
int		check_pipe(char *line);
void	stderr_exit_f(const char *str1, const char *str2, int r, t_error *err);
void	stderr_exit_t(const char *str1, const char *str2, int r, t_error *err);
void	stderr_cd(const char *str1, int r, t_error *err);
void	check_here_doc(char *input);

// exec

int		exec_line(t_cmd *cmd, t_list **list, t_error *err);
char	*ft_join(const char *s1, const char *s2);
char	*find_path(char *cmd, char *path, char *pwd);

// gnl

char	*get_next_line(int fd);

#endif
