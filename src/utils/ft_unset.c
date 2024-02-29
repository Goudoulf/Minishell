/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:26:14 by cassie            #+#    #+#             */
/*   Updated: 2024/02/29 13:55:03 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdel(t_list **lst, char *cmd)
{
	t_list	*temp;
	t_list	*current;
	char	*var_cmd;

	if (!lst)
		return ;
	current = *lst;

	while (current != NULL)
	{
		temp = current->next;
		free(current->string);
		free(current->var);
		free(current->var_content);
		free(current);
		current = temp;
	}
	*lst = NULL;
}

static t_list	*check_cmd_env(char *arg, t_list **env)
{
	t_list	*temp;

	temp = *env;
	while (temp)
	{
		if (!ft_strcmp(temp->var, arg, ft_strlen(arg)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	ft_unset(t_list **env, char **cmd)
{
	int		i;
	t_list *temp;

	i = 1;
	temp = NULL;
	if (tab_size(cmd) < 2)
		return (0);
	while (cmd[i])
	{
		temp = check_cmd_env(cmd[i], env);
		if (temp)
			env_update(temp, cmd[i]);
		i++;
	}
	return (0);
}
