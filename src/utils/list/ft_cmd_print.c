/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:28:38 by cassie            #+#    #+#             */
/*   Updated: 2024/03/15 19:05:12 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_print(t_cmd **cmd)
{
	t_cmd	*temp;
	int		d;
	int		i;
	int		j;
	int		k;

	d = 0;
	temp = *cmd;
	while (temp != NULL)
	{
		i = -1;
		j = -1;
		k = -1;
		printf("Block[%d]\n", d++);
		while (temp->cmd && temp->cmd[++i])
			printf("	cmd[%d] =%s\n", i, temp->cmd[i]);
		while (temp->redirection && temp->redirection[++j])
			printf("	redirection[%d] =%s\n", j, temp->redirection[j]);
		while (temp->here_doc && temp->here_doc[++k])
			printf("	here_doc[%d] =%s\n", k, temp->here_doc[k]);
		temp = temp->next;
	}
}
