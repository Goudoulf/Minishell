/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:12:26 by cassie            #+#    #+#             */
/*   Updated: 2024/03/19 15:34:45 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <readline/readline.h>
#include <stdlib.h>

#define CYELLOW "\001\e[0;31m\002"
#define RESET   "\001\e[0m\002"

static void	quit_eof(t_list **env, t_cmd **cmd, t_error *err)
{
	rl_clear_history();
	ft_lstclear(env);
	ft_cmdclear(cmd);
	//ft_putstr_fd("exit\n", 1);
	exit(err->code);
}

static void	quit_exit(t_list **env, t_cmd **cmd, t_error *err)
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

int main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	t_list	*env;
	t_error	err;
	char	*input;

	env = NULL;
	cmd = NULL;
	if (!init_all(&env, &err, envp, &cmd))
		quit_error(&err);
	(void)argv;
	(void)argc;
	while(1)
	{
		signal_handling();
		if (isatty(fileno(stdin)))
		{
			input = readline(CYELLOW "[Minishell]: " RESET);
		}
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			input = ft_strtrim(line, "\n");
			free(line);
		}
		if (!input)
			quit_eof(&env, &cmd, &err);
		signal_handling_child();
		if (input && *input)
		{
			err.input = &input;
			add_history(input);
			if (check_line_error(input, &err))
			{
				line_parsing(&cmd, input, &env, &err);
				err.code = exec_line(cmd, &env, &err);
			}
			else
				check_here_doc(input, -1);
			ft_cmdclear(&cmd);
		}
		free(input);
		if (err.do_exit == true)
			quit_exit(&env, &cmd, &err);
	}
}
