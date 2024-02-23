/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:15:38 by cassie            #+#    #+#             */
/*   Updated: 2024/02/23 16:24:37 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/includes/libft.h"
# include "../lib/ft_printf/includes/ft_printf.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	char			*string;
	char			*var;
	char			*var_content;
	struct s_list	*next;
}				t_list;

typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	char			**input_file;
	char			**output_file;
	struct s_cmd	*next;
}				t_cmd;

// core
void	check_cmd(char *input, t_list **env);

// cmd
int	ft_echo(char *str, char *arg, t_list **env);
int	ft_pwd(void);

// init

void	init_all(t_cmd **cmd, t_list **env, char **envp);

// utils

char *ft_strtok(char *string, char *delim);
char *ft_strtok_quote(char *string, char *delim);
size_t infile_count(char *line);
size_t outfile_count(char *line);

// list

t_list	*ft_lst_new(char *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lst_print(t_list **list);
void	ft_lstclear(t_list **lst);

// parsing

void	line_parsing(t_cmd **cmd, char *line);
char	*clean_line(char *line);
char	**split_pipe(char *line);
void	line_to_cmd(t_cmd **cmd, char *line);

size_t	cmd_count(char const *s, char c);
size_t infile_count(char *line);
size_t outfile_count(char *line);

#endif
