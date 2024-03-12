/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:14:44 by cassie            #+#    #+#             */
/*   Updated: 2024/02/29 10:24:16 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_print(t_list **list, int fd)
{
	t_list	*temp;

	temp = *list;
	while (temp != NULL)
	{
		ft_printf(fd, "%s=%s\n", temp->var, temp->var_content);
		//printf("var = %s\n", temp->var);
		//printf("var_content = %s\n", temp->var_content);
		temp = temp->next;
	}
}
