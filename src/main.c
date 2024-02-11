/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:12:26 by cassie            #+#    #+#             */
/*   Updated: 2024/02/11 15:45:24 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define CYELLOW "\001\e[0;31m\002"
#define RESET   "\001\e[0m\002"

int main(void)
{
	char *input;

	while(1)
	{
		input = readline(CYELLOW "[Minishell]: " RESET);
		if (input && *input)
			add_history(input);
		if (input && !ft_strncmp(input, "exit", 4))
		{
			free(input);
			rl_clear_history();
			exit(0);
		}
		free(input);
	}
}

