/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:20:17 by cassie            #+#    #+#             */
/*   Updated: 2024/03/15 09:15:35 by cassie           ###   ########.fr       */
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

static unsigned char	ft_char_to_num(const char *str)
{
	int			i;
	int			c;
	long long int	result;
	long long int	old_result;

	i = 0;
	result = 0;
	old_result = 0;
	c = ft_sign(str, i);
	if (str[i] == 45 || str[i] == 43)
		i++;
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		if (c > 0 && (result * c < 0))
			return (-1);
		if (c < 0 && (result * c > 0))
			return (0);
		result = result * 10 + (str[i] - '0');
		if (result < old_result)
			return (unsigned char)-2;
		old_result = result;
		if ((str[i + 1] < 48) || (str[i + 1] > 57))
			return ((unsigned char)result * c);
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

void	ft_exit(char **cmd, t_error *err)
{
	unsigned char code;

	if (tab_size(cmd) < 2)
	{
		err->do_exit = true;
		//ft_putstr_fd("exit\n", 2);
		return ;
	}
	if (tab_size(cmd) > 2)
	{	
		if (!arg_is_valid(cmd[1]))
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			err->code = 1;
			return ;
		}
		else
		{
			err->do_exit = true;
			err->code = 2;
			//ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
		}
	}
	if (tab_size(cmd) == 2)
	{
		if (cmd[1][0] && !arg_is_valid(cmd[1]))
		{
			err->do_exit = true;
			code = ft_char_to_num(cmd[1]);
			if (code == (unsigned char)-2 && ft_atoi(cmd[1]) != -2)
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(cmd[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				err->code = 2;
				return ;
			}
			err->code = code;
			return ;
		}
		err->do_exit = true;
		err->code = 2;
		//ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
}
