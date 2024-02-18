/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:14:44 by cassie            #+#    #+#             */
/*   Updated: 2024/02/18 13:11:25 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_print(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp != NULL)
	{
		printf("%s\n", temp->string);
		//printf("var = %s\n", temp->var);
		//printf("var_content = %s\n", temp->var_content);
		temp = temp->next;
	}
}
