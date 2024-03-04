/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:28:38 by cassie            #+#    #+#             */
/*   Updated: 2024/03/04 11:41:00 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_print(t_cmd **cmd)
{
	t_cmd	*temp;
	int	d;

	d = 0;
	temp = *cmd;
	while (temp != NULL)
	{
		int	i = 0;
		int	j = 0;
		printf("Block[%d]\n", d++);
		while (temp->cmd && temp->cmd[i])
		{
			printf("	cmd[%d] =%s\n",i, temp->cmd[i]);
			i++;
		}
		while (temp->redirection && temp->redirection[j])
		{
			printf("	redirection[%d] =%s\n", j, temp->redirection[j]);
			j++;
		}
		temp = temp->next;
	}
}
