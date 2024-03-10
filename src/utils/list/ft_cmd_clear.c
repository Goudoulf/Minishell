/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 09:54:13 by cassie            #+#    #+#             */
/*   Updated: 2024/03/09 11:22:01 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmdclear(t_cmd **cmd)
{
	t_cmd	*temp;
	t_cmd	*current;

	if (!cmd)
		return ;
	current = *cmd;
	while (current != NULL)
	{
		temp = current->next;
		free_tab(current->cmd);
		if (current->cmd)
			free(current->cmd);
		if (current->path)
			free(current->path);
		free_tab(current->redirection);
		if (current->redirection)
			free(current->redirection);
		free(current);
		current = temp;
	}
	*cmd = NULL;
}
