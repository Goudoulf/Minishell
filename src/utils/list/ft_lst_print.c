/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq < rjacq@student.42lyon.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:14:44 by cassie            #+#    #+#             */
/*   Updated: 2024/03/13 13:34:15 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_print(t_list **list, t_error *err)
{
	t_list	*temp;

	temp = *list;
	while (temp != NULL)
	{
		ft_printf("%s=%s\n", temp->var, temp->var_content);
		//printf("var = %s\n", temp->var);
		//printf("var_content = %s\n", temp->var_content);
		temp = temp->next;
	}
	err->code = 0;
}
