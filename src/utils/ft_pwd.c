/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 08:03:34 by cassie            #+#    #+#             */
/*   Updated: 2024/03/09 14:15:15 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **cmd)
{
	char	*str;
	char	*temp;
	int		size;
	int		i;

	str = NULL;
	size = 10;
	i = 1;
	if (tab_size(cmd) > 2)
	{
		ft_putstr_fd("pwd : too many arguments\n", 2);
		exit (1);
	}
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		exit (1);
	str[size] = '\0';
	while (i)
	{
		temp = getcwd(str, size * i);
		if (!temp)
		{
			free(str);
			i++;
			str = malloc(sizeof(char) * size * i + 1);
			if (!str)
				exit (1);
			str[size * i] = '\0';
		}
		else 
		{
			ft_printf("%s\n", temp);
			free(str);
			exit (0);
		}
	}
	exit (0);
}
