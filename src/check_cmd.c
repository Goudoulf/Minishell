/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:06:40 by cassie            #+#    #+#             */
/*   Updated: 2024/02/29 10:22:29 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(char *input, t_list **env, t_cmd **cmd)
{
	if (!input)
	{
		rl_clear_history();
		ft_lstclear(env);
		ft_printf("exit\n");
		exit(0);
	}
	if (input && !ft_strncmp(input, "exit", 5))
	{
		free(input);
		rl_clear_history();
		ft_cmdclear(cmd);
		ft_lstclear(env);
		ft_printf("exit\n");
		exit(0);
	}
	if (!ft_strncmp(input, "echo", 5))
		ft_echo(&input[5], NULL, env);
	if (!ft_strncmp(input, "pwd", 4))
		ft_pwd();
	if (!ft_strncmp(input, "env", 5))
		ft_lst_print(env);
}
