/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:12:26 by cassie            #+#    #+#             */
/*   Updated: 2024/02/16 15:33:35 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signal.h>

#define CYELLOW "\001\e[0;31m\002"
#define RESET   "\001\e[0m\002"


void sigint_handler(int	sig)
{
	(void)sig;
	write(0, "\n", 1);
	rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void sigquit_handler(int sig)
{
	(void)sig;
}

int main(void)
{
	char *input;
	struct sigaction old_action;
	struct sigaction action;

	while(1)
	{
		action.sa_handler = &sigint_handler;
		sigaction(SIGINT, &action, &old_action);
		action.sa_handler = &sigquit_handler;
		sigaction(SIGQUIT, &action, &old_action);
		input = readline(CYELLOW "[Minishell]: " RESET);
		if (input && *input)
			add_history(input);
		if ((input && !ft_strncmp(input, "exit", 4))|| !input)
		{
			free(input);
			rl_clear_history();
			exit(0);
		}
		free(input);
	}
}
