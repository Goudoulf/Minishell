/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq < rjacq@student.42lyon.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:58:48 by rjacq             #+#    #+#             */
/*   Updated: 2024/02/22 16:41:11 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
//# include "../includes/minishell.h"
# include "../lib/libft/includes/libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
    char            *string;
    char            *var;
    char            *var_content;
    struct s_list    *next;
}                t_list;

typedef struct s_cmd
{
    char            **cmd;
    char            *path;
    char            **input_file;
    char            **output_file;
    struct s_cmd    *next;
}                t_cmd;

int		isdirectory(char *str);
char	*get_cmd_path(char *cmd, char *envp[]);
char	**ft_split(char const *s, char c);
void	free_string_tab(char **c);

#endif
