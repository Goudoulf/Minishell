/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:48:48 by cassie            #+#    #+#             */
/*   Updated: 2024/03/16 09:28:13 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_err(t_error *err)
{
	err->code = 0;
	err->do_exit = false;
}

static t_list	**init_env_list(t_list **env, char **envp)
{
	int	i;

	i = -1;
	if (!*envp)
	{
		ft_lstadd_back(env, ft_lst_new(ft_strjoin("PWD=", ft_pwd2(10, 1))));
		ft_lstadd_back(env, ft_lst_new("OLDPWD"));
		ft_lstadd_back(env, ft_lst_new("SHLVL=1"));
		ft_lstadd_back(env, ft_lst_new("_=/usr/bin/env"));
		return (env);
	}
	while (envp[++i])
		ft_lstadd_back(env, ft_lst_new(envp[i]));
	return (env);
}

void	init_all(t_cmd **cmd, t_list **env, t_error *err, char **envp)
{
	init_env_list(env, envp);
	if (*envp)
		inc_shell_lvl(env);
	init_err(err);
	(void)cmd;
}
