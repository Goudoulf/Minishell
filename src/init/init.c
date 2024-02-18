/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:48:48 by cassie            #+#    #+#             */
/*   Updated: 2024/02/18 12:59:33 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_env_list(t_list **env, char **envp)
{
	int	i;

	i = -1;
	if (!envp)
		return ;
	//*env = ft_lst_new(envp[i]);
	while (envp[++i])
		ft_lstadd_back(env, ft_lst_new(envp[i]));
}

void	init_all(t_list **env, char **envp)
{
	init_env_list(env, envp);
}
