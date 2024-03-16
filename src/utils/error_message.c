/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:34:15 by cassie            #+#    #+#             */
/*   Updated: 2024/03/16 10:58:28 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stderr_c(const char *str1, const char c, const char *str3, int ret)
{
	write(2, "minishell: ", 11);
	write(2, str1, ft_strlen(str1));
	if (c == '\0')
		write(2, "newline", 7);
	else
		write(2, &c, 1);
	write(2, str3, ft_strlen(str3));
	write(2, "\n", 1);
	return (ret);
}

void	stderr_exit_f(const char *str1, const char *str2, int r, t_error *err)
{
	write(2, "minishell: exit: ", 17);
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	err->code = r;
}

void	stderr_exit_t(const char *str1, const char *str2, int r, t_error *err)
{
	//ft_putstr_fd("exit\n", 2);
	write(2, "minishell: exit: ", 17);
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	err->code = r;
	err->do_exit = true;
}

void	stderr_cd(const char *str1, int r, t_error *err)
{
	write(2, "minishell: cd: ", 16);
	write(2, str1, ft_strlen(str1));
	write(2, "\n", 1);
	err->code = r;
}
