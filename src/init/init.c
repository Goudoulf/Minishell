/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:48:48 by cassie            #+#    #+#             */
/*   Updated: 2024/03/19 15:52:00 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_err(t_error *err, t_list **env, t_cmd **cmd)
{
	err->code = 0;
	err->do_exit = false;
	err->cmd = cmd;
	err->env = env;
}

static size_t	ft_lstsize(t_list *lst)
{
	size_t	i;
	t_list	*tmp;

	tmp = lst;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

static t_list	**init_env_list(t_list **env, char **envp, int i)
{
	t_list	*temp;

	if (!*envp)
	{
		temp = ft_lst_new(ft_strjoin("PWD=", ft_pwd2(10, 1)));
		ft_lstadd_back(env, temp);
		temp = ft_lst_new("OLDPWD");
		ft_lstadd_back(env, temp);
		temp = ft_lst_new("SHLVL=1");
		ft_lstadd_back(env, temp);
		temp = ft_lst_new("_=/usr/bin/env");
		ft_lstadd_back(env, temp);
		temp = *env;
		if (ft_lstsize(temp) < 4)
			return (NULL);
		return (env);
	}
	while (envp[++i])
		ft_lstadd_back(env, ft_lst_new(envp[i]));
	temp = *env;
	if (ft_lstsize(temp) != tab_size(envp))
		return (NULL);
	return (env);
}

int	init_all(t_list **env, t_error *err, char **envp, t_cmd **cmd)
{
	init_err(err, env, cmd);
	if (!init_env_list(env, envp, -1))
		return (0);
	if (*envp)
	{
		if (!inc_shell_lvl(env))
			return (0);
	}
	return (1);
}
