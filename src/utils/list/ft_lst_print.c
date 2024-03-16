/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:14:44 by cassie            #+#    #+#             */
/*   Updated: 2024/03/15 19:05:39 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_print(t_list **list, t_error *err, int fd)
{
	t_list	*temp;

	temp = *list;
	while (temp != NULL)
	{
		if (temp->var_content)
			ft_printf(fd, "%s=%s\n", temp->var, temp->var_content);
		temp = temp->next;
	}
	err->code = 0;
}
