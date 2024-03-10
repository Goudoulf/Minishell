/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:04:47 by cassie            #+#    #+#             */
/*   Updated: 2024/03/09 11:21:11 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static char	**create_tab(char **tab, size_t nelem)
{
	size_t	i;

	i = 0;
	tab = malloc(sizeof(char *) * (nelem + 1));
	if (!tab)
		return (NULL);
	while (i < nelem)
	{
		tab[i] = NULL;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}*/

static size_t	pipe_count(char *line)
{
	size_t pipe_count;
	int	i;

	i = 0;
	pipe_count = 0;
	while (line[i])
	{
		if (line[i] == '|')
			pipe_count++;
		i++;
	}
	return (pipe_count + 1);
}

char	**split_pipe(char *line)
{
	size_t	n_pipe;
	int		i;
	char	**temp_tab;
	char	*delim;
	char	*token;

	temp_tab = NULL;
	i = 0;
	if (!line)
		return (NULL);
	n_pipe = pipe_count(line);
	delim = "|";
	temp_tab = create_tab(n_pipe); 
	token = ft_strtok_quote(line, delim);
	while (token)
	{
		temp_tab[i] = ft_strdup(token);
		token = ft_strtok_quote(NULL, delim);
		i++;
	}
	free(line);
	return (temp_tab);
}
