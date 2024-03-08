/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:26:14 by cassie            #+#    #+#             */
/*   Updated: 2024/02/29 19:15:19 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	tab_size(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

static void	free_link(t_list *env_link)
{
	if (env_link->var)
		free(env_link->var);
	if (env_link->var_content)
		free(env_link->var_content);
	free(env_link);
}

static void	ft_lstdel(t_list **lst, char *cmd)
{
	t_list	*temp;
	t_list	*current;
	t_list	*next_current;

	if (!lst)
		return ;
	current = *lst;
	next_current = current->next;
	if (!ft_strncmp(current->var, cmd, ft_strlen(cmd)))
	{
		*lst = next_current;
		free_link(current);
		return ;
	}
	while (next_current)
	{
		temp = next_current->next;
		if (!ft_strncmp(next_current->var, cmd, ft_strlen(cmd)))
		{
			free_link(next_current);
			current->next = temp;
			return ;
		}
		current = next_current;
		next_current = temp;
	}
}

/*static t_list	*check_cmd_env(char *arg, t_list **env)
{
	t_list	*temp;

	temp = *env;
	while (temp)
	{
		if (!ft_strncmp(temp->var, arg, ft_strlen(arg)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}*/

int	ft_unset(t_list **env, char **cmd)
{
	int		i;

	i = 1;
	if (tab_size(cmd) < 2)
		return (0);
	while (cmd[i])
	{
		ft_lstdel(env, cmd[i]);
		i++;
	}
	return (0);
}
