/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:30:06 by cassie            #+#    #+#             */
/*   Updated: 2024/03/18 10:56:30 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmd_new(char **redirection)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->path = NULL;
	new->redirection = redirection;
	new->here_doc = NULL;
	new->next = NULL;
	new->pid = -1;
	return (new);
}

void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*temp;

	temp = *cmd;
	if (new == NULL)
		return ;
	if (*cmd == NULL)
	{
		*cmd = new;
		new->next = NULL;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	cmd_add_path(t_cmd **cmd, t_list **env)
{
	t_cmd	*temp;
	char	*path;
	char	*pwd;

	temp = *cmd;
	path = get_value(env, "PATH");
	pwd = get_value(env, "PWD");
	while (temp)
	{
		if (temp->cmd)
			temp->path = find_path(temp->cmd[0], path, pwd);
		else
			temp->path = NULL;
		temp = temp->next;
	}
}
