/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:20:17 by cassie            #+#    #+#             */
/*   Updated: 2024/03/16 10:57:45 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_sign(const char *str, int i )
{
	int	c;

	c = 1;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == '-')
			c = c * -1;
	}
	return (c);
}

static unsigned char	ft_char_to_num(const char *str, int i, long long int r)
{
	int				c;
	long long int	old_r;

	old_r = 0;
	c = ft_sign(str, i);
	if (str[i] == 45 || str[i] == 43)
		i++;
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		if (c > 0 && (r * c < 0))
			return (-1);
		if (c < 0 && (r * c > 0))
			return (0);
		r = r * 10 + (str[i] - '0');
		if (r < old_r)
			return (-2);
		old_r = r;
		if ((str[i + 1] < 48) || (str[i + 1] > 57))
			return ((unsigned char)r * c);
		i++;
	}
	return (0);
}

static int	arg_is_valid(char *arg)
{
	int	i;

	i = 0;
	if (!(arg[i] != '+' || arg[i] != '-' || ft_isdigit(arg[i])))
		return (1);
	if ((arg[i] == '+' || arg[i] == '-') && !(ft_isdigit(arg[i + 1])))
		return (1);
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

static void	only_exit(t_error *err)
{
	err->do_exit = true;
	err->code = 0;
	//ft_putstr_fd("exit\n", 2);
}

void	ft_exit(char **cmd, t_error *err, unsigned char code)
{
	if (tab_size(cmd) < 2)
		only_exit(err);
	if (tab_size(cmd) > 2)
	{
		if (!arg_is_valid(cmd[1]))
			return (stderr_exit_f("too many arguments", "\0", 1, err));
		else
			stderr_exit_t(cmd[1], ": numeric argument required", 2, err);
	}
	if (tab_size(cmd) == 2)
	{
		if (cmd[1][0] && !arg_is_valid(cmd[1]))
		{
			err->do_exit = true;
			code = ft_char_to_num(cmd[1], 0, 0);
			if (code == (unsigned char)-2 && ft_atoi(cmd[1]) != -2)
				return (stderr_exit_f(cmd[1], ": numeric argument required",
						2, err));
			err->code = code;
			return ;
		}
		stderr_exit_t(cmd[1], ": numeric argument required", 2, err);
	}
}
