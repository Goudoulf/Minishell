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


int main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	t_list	*env;
	t_error	err;
	char	*input;

	(void)argc;
	(void)argv;
	env = NULL;
	cmd = NULL;
	init_all(&cmd, &env, &err, envp);
	// a ajouter dans heredoc
	signal_handling();
	while(1)
	{
		input = readline(CYELLOW "[Minishell]: " RESET);
		if (!input)
		{
			rl_clear_history();
			ft_lstclear(&env);
			ft_cmdclear(&cmd);
			ft_printf("exit\n");
			exit(0);
		}
		if (input && *input)
		{
			add_history(input);
			if (check_line_error(input))
				line_parsing(&cmd, input, &env, &err);
			else
			{
				ft_putstr_fd("error\n", 2);
				free(input);
				input = NULL;
			}
			exec_line(cmd, envp);
		}
		if (input)
		{
			check_cmd(input, &env, &cmd, &err);
			ft_cmdclear(&cmd);
			free(input);
		}
	}
	ft_lstclear(&env);
	free(env);
}
