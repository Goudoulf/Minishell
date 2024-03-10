/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:12:26 by cassie            #+#    #+#             */
/*   Updated: 2024/02/18 17:48:52 by cassie           ###   ########.fr       */
/*   Updated: 2024/02/16 15:33:35 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CYELLOW "\001\e[0;31m\002"
#define RESET   "\001\e[0m\002"

static void	quit_eof(t_list **env, t_cmd **cmd, t_error *err)
{
	rl_clear_history();
	ft_lstclear(env);
	ft_cmdclear(cmd);
	ft_putstr_fd("exit\n", 1);
	exit(err->code);
}

int main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	t_list	*env;
	t_error	err;
	char	*input;
	char **env_tab;

	env = NULL;
	cmd = NULL;
	init_all(&cmd, &env, &err, envp);
	signal_handling();
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		input = argv[2];
		if (!input)
			quit_eof(&env, &cmd, &err);
		if (input && *input)
		{
			add_history(input);
			if (check_line_error(input))
			{
				line_parsing(&cmd, input, &env, &err);
				env_tab = ft_lst_to_tab(&env);
				err.code = exec_line(cmd, env_tab);
			//	check_cmd(input, &env, &cmd, &err);
			}
			else
			{
				err.code = 2;
				ft_putstr_fd("error\n", 2);
			}
			ft_cmdclear(&cmd);
		}
		exit(err.code);
	}
	while(1)
	{
		input = readline(CYELLOW "[Minishell]: " RESET);
		if (!input)
			quit_eof(&env, &cmd, &err);
		if (input && *input)
		{
			add_history(input);
			if (check_line_error(input))
			{
				line_parsing(&cmd, input, &env, &err);
				env_tab = ft_lst_to_tab(&env);
				exec_line(cmd, env_tab);
			//	check_cmd(input, &env, &cmd, &err);
			}
			else
			{
				err.code = 2;
				ft_putstr_fd("error\n", 2);
			}
			ft_cmdclear(&cmd);
		}
		free(input);
	}
}
