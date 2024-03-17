/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:11:43 by cassie            #+#    #+#             */
/*   Updated: 2024/03/17 16:27:49 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	global;

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_h(int sig)
{
	(void)sig;
	write(2, "Quit\n", 5);
}

void	sigint_handler_hd(int sig)
{
	(void)sig;
	global = 1;
}

static void	sigint_handler_child(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

static void	sigquit_handler(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

static void	sigquit_handler_child(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &sigquit_h;
	sigaction(SIGQUIT, &act, NULL);
}


void	signal_handling(void)
{
	struct sigaction	act;

	sigquit_handler();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
}

void	signal_handling_child(void)
{
	struct sigaction	act;

	sigquit_handler_child();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &sigint_handler_child;
	sigaction(SIGINT, &act, NULL);
}

void	signal_handling_hd(void)
{
	struct sigaction	act;

	sigquit_handler();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &sigint_handler_hd;
	sigaction(SIGINT, &act, NULL);
}
