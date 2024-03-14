/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:26:14 by cassie            #+#    #+#             */
/*   Updated: 2024/03/14 10:16:14 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	cmd_is_valid(char *cmd)
{
	int i;

	i = 0;
	if (cmd && (ft_isdigit(cmd[i])))
	{
		ft_putstr_fd("minishell: line 0: export: `", 2);
		write(2, &cmd[i], 1);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		return (0);
	}
	while (cmd[i])
	{
		if (ft_isalnum(cmd[i]) || cmd[i] == '_')
			i++;
		else
		{
			ft_putstr_fd("minishell: line 0: export: `", 2);
			ft_putstr_fd(cmd, 2);
			//write(2, &cmd[i], 1);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			return (0);
		}
	}
	return (1);
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

int	ft_unset(t_list **env, char **cmd, t_error *err)
{
	int		i;

	i = 1;
	if (tab_size(cmd) < 2)
		return (0);
	if (tab_size(cmd) == 2 && cmd[1][0] == '\0')
	{
		ft_putstr_fd("minishell: unset: `': not a valid identifier\n", 2);
		err->code = 1;
		return (1);
	}
	while (cmd[i])
	{
		if (!cmd_is_valid(cmd[i]))
		{
			err->code = 1;
			return (0);
		}
		ft_lstdel(env, cmd[i]);
		i++;
	}
	err->code = 0;
	return (0);
}
