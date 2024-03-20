/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:04:47 by cassie            #+#    #+#             */
/*   Updated: 2024/03/20 09:24:31 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**clear_tab(char **tab, int i, char *line)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	if (line)
		free(line);
	return (NULL);
}

static size_t	pipe_count(char *line)
{
	size_t	pipe_count;
	int		i;

	i = 0;
	pipe_count = 0;
	while (line && line[i])
	{
		if (line[i] == '|')
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

char	**split_pipe(char *line, t_error *err)
{
	size_t	n_pipe;
	int		i;
	char	**temp_tab;
	char	*delim;
	char	*token;

	temp_tab = NULL;
	i = 0;
	n_pipe = pipe_count(line);
	delim = "|";
	temp_tab = create_tab(n_pipe + 1);
	token = ft_strtok_quote(line, delim);
	while (token && temp_tab)
	{
		temp_tab[i] = ft_strdup(token);
		if (!temp_tab[i])
			clear_tab(temp_tab, i - 1, line);
		token = ft_strtok_quote(NULL, delim);
		i++;
	}
	free(line);
	if (!temp_tab)
		quit_error(err);
	return (temp_tab);
}
