/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_min.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:11:17 by cassie            #+#    #+#             */
/*   Updated: 2024/03/15 20:59:34 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_next_min(t_list **stack)
{
	t_list	*head;
	t_list	*min;
	int		new_min;

	min = NULL;
	new_min = 0;
	head = *stack;
	if (!head)
		return (min);
	while (head)
	{
		if ((head->isprint == -1) && (!new_min
				|| ft_strncmp(min->var, head->var, ft_strlen(head->var)) > 0))
		{
			min = head;
			new_min = 1;
		}
		head = head->next;
	}
	if (min)
		min->isprint = 1;
	return (min);
}
