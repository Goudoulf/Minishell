/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:16:20 by cassie            #+#    #+#             */
/*   Updated: 2024/03/18 15:00:41 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	tab_size(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	if (!tab)
		return ;
	while (*tab)
	{
		free(*tab);
		tab++;
	}
}

char	**create_tab(size_t nelem)
{
	size_t	i;
	char	**tab;

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
