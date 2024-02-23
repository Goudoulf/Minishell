/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:06:40 by cassie            #+#    #+#             */
/*   Updated: 2024/02/23 10:36:52 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(char *input, t_list **env)
{
	if (!input)
	{
		rl_clear_history();
		ft_lstclear(env);
		ft_printf("exit\n");
		exit(0);
	}
	if (input && !ft_strncmp(input, "exit", 4))
	{
		free(input);
		rl_clear_history();
		ft_lstclear(env);
		ft_printf("exit\n");
		exit(0);
	}
	if (!ft_strncmp(input, "echo", 4))
		ft_echo(&input[5], NULL, env);
	if (!ft_strncmp(input, "pwd", 4))
		ft_pwd();
	if (!ft_strncmp(input, "env", 4))
		ft_lst_print(env);
}
