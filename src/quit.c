/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:14:56 by cassie            #+#    #+#             */
/*   Updated: 2024/03/20 10:08:45 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_eof(t_list **env, t_cmd **cmd, t_error *err)
{
	rl_clear_history();
	ft_lstclear(env);
	ft_cmdclear(cmd);
	ft_putstr_fd("exit\n", 2);
	exit(err->code);
}

void	quit_exit(t_list **env, t_cmd **cmd, t_error *err)
{
	rl_clear_history();
	ft_lstclear(env);
	ft_cmdclear(cmd);
	exit(err->code);
}

void	quit_error(t_error *err)
{
	rl_clear_history();
	ft_lstclear(err->env);
	ft_cmdclear(err->cmd);
	if (*(err->input))
		free(*(err->input));
	ft_putstr_fd("malloc error\n", 2);
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_FAILURE);
}
