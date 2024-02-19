/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:48:48 by cassie            #+#    #+#             */
/*   Updated: 2024/02/19 14:29:07 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_env_list(t_list **env, char **envp)
{
	int	i;

	i = -1;
	if (!envp)
		return ;
	while (envp[++i])
		ft_lstadd_back(env, ft_lst_new(envp[i]));
}

void	init_all(t_data **data, char **envp)
{
	init_env_list(&(data->env), envp);
}
