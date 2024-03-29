/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:25:03 by cassie            #+#    #+#             */
/*   Updated: 2024/03/20 09:27:21 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	size_of_heredoc(char **redirect)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	if (!redirect)
		return (0);
	while (redirect[i])
	{
		if (redirect[i][0] == '<' && redirect[i][1] == '<')
			size++;
		i++;
	}
	return (size);
}

static char	**create_here_doc(char **redirect, t_error *err, int i, int j)
{
	size_t	size;
	char	**tab;

	size = size_of_heredoc(redirect);
	if (!size)
		return (NULL);
	tab = create_tab(size);
	if (!tab)
		quit_error(err);
	while (redirect[++i])
	{
		if (redirect[i][0] == '<' && redirect[i][1] == '<')
		{
			tab[j] = ft_strdup(redirect[i]);
			if (!tab[j])
			{
				free_tab(tab);
				free(tab);
				quit_error(err);
			}
			j++;
		}
	}
	return (tab);
}

static char	**delete_here_doc(char **redirect, int i, int j)
{
	size_t	size;
	size_t	count;
	char	**tab;

	count = 1;
	size = size_of_heredoc(redirect);
	if (!size || size == 1)
		return (redirect);
	tab = create_tab(tab_size(redirect) - size + 1);
	while (redirect[i])
	{
		if (redirect[i][0] == '<' && redirect[i][1] == '<')
		{
			if (count == size)
				tab[j++] = ft_strdup(redirect[i]);
			i++;
			count++;
		}
		else
			tab[j++] = ft_strdup(redirect[i++]);
	}
	free_tab(redirect);
	free(redirect);
	return (tab);
}

void	clean_redirection(t_cmd **cmd, t_error *err)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		if (temp->redirection)
		{
			temp->here_doc = create_here_doc(temp->redirection, err, -1, 0);
			temp->redirection = delete_here_doc(temp->redirection, 0, 0);
		}
		temp = temp->next;
	}
}
