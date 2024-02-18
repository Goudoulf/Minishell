/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:12:26 by cassie            #+#    #+#             */
/*   Updated: 2024/02/18 17:48:52 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define CYELLOW "\001\e[0;31m\002"
#define RESET   "\001\e[0m\002"

// use getenv()

int main(int argc, char **argv, char **envp)
{
	char *input;
	t_list	*env;

	(void)argc;
	(void)argv;
	env = NULL;
	init_all(&env, envp);
	while(1)
	{
		input = readline(CYELLOW "[Minishell]: " RESET);
		if (input && *input)
			add_history(input);
		check_cmd(input, &env);
		free(input);
	}
}
