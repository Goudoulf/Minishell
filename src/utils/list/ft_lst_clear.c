/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:12:52 by cassie            #+#    #+#             */
/*   Updated: 2024/03/04 10:32:14 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;
	t_list	*current;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		temp = current->next;
		free(current->string);
		free(current->var);
		free(current->var_content);
		current->isprint = 0;
		free(current);
		current = temp;
	}
	*lst = NULL;
}

