/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:32:24 by cassie            #+#    #+#             */
/*   Updated: 2024/03/09 13:53:01 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_lstsize(t_list **lst)
{
	int	i;
	t_list	*tmp;

	tmp = *lst;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**ft_lst_to_tab(t_list **list)
{
	t_list	*temp;
	char	**tab;
	char	*temp1;
	int		size;
	int		i;

	temp = *list;
	if (!temp)
		return (NULL);
	i = 0;
	size = ft_lstsize(list);
	tab = create_tab(size);
	while (temp != NULL)
	{
		if (!temp->var_content)
			tab[i] = ft_strdup(temp->var);
		else if	(temp->var && temp->var_content)
		{
			temp1 = ft_strjoin(temp->var, "=");
			tab[i] = ft_strjoin(temp1, temp->var_content);
			free(temp1);
		}
		i++;
		temp = temp->next;
	}
	return (tab);
}
