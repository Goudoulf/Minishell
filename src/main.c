/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:12:26 by cassie            #+#    #+#             */
/*   Updated: 2024/02/14 13:35:51 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signal.h>

#define CYELLOW "\001\e[0;31m\002"
#define RESET   "\001\e[0m\002"

struct sigaction old_action;
struct sigaction action;

void sigint_handler(int	sig_no)
{
	sig_no = 0;
}


int main(void)
{
	char *input;

	while(1)
	{
		memset(&action, 0, sizeof(action));
		action.sa_handler = &sigint_handler;
		sigaction(SIGINT, &action, &old_action);
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

