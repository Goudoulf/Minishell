/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 09:54:13 by cassie            #+#    #+#             */
/*   Updated: 2024/02/27 16:09:19 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tab(char **tab)
{
	if (!tab)
		return ;
	while (*tab)
	{
		free(*tab);
		tab++;
	}
}

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
		//if (current->path)
		//	free(current->path);
		free_tab(current->input_file);
		if (current->input_file)
			free(current->input_file);
		free_tab(current->output_file);
		if (current->output_file)
			free(current->output_file);
		free(current);
		current = temp;
	}
	*cmd = NULL;
}
