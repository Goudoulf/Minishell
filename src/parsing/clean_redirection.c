/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:25:03 by cassie            #+#    #+#             */
/*   Updated: 2024/03/08 13:08:17 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	tab_size(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

static void	free_tab(char **tab)
{
	if (!tab)
		return ;
	while (*tab)
	{
		free(*tab);
		tab++;
	}
}

static char	**create_tab(size_t nelem)
{
	size_t	i;
	char **tab;

	i = 0;
	tab = NULL;
	if (nelem == 0)
		return (NULL);
	tab = malloc(sizeof(char *) * (nelem + 1));
	if (!tab)
		return (NULL);
	while (i < nelem)
	{
		tab[i] = NULL;
		i++;
	}
	tab[i] = 0; 
	return (tab);
}

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

static char	**create_here_doc(char **redirect)
{
	size_t size;
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	size = size_of_heredoc(redirect);
	if (!size)
		return (NULL);
	tab = create_tab(size);
	while (redirect[i])
	{
		if (redirect[i][0] == '<' && redirect[i][1] == '<')
		{
			tab[j] = ft_strdup(redirect[i]);
			j++;
		}
		i++;
	}
	return (tab);
}

static char	**delete_here_doc(char **redirect)
{
	size_t size;
	int		i;
	int		j;
	size_t		count;
	char	**tab;

	i = 0;
	j = 0;
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
			{
				tab[j] = ft_strdup(redirect[i]);
				j++;
			}
			i++;
			count++;
		}
		else
		{
			tab[j] = ft_strdup(redirect[i]);
			i++;
			j++;
		}
	}
	free_tab(redirect);
	free(redirect);
	return (tab);
}

void	clean_redirection(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		if (temp->redirection)
		{
			temp->here_doc = create_here_doc(temp->redirection);
			temp->redirection = delete_here_doc(temp->redirection);
		}
		temp = temp->next;
	}
}
