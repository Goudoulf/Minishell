/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq < rjacq@student.42lyon.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 08:03:34 by cassie            #+#    #+#             */
/*   Updated: 2024/03/13 13:34:47 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **cmd, t_error *err)
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
		return (1);
	}
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (1);
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
				return (1);
			str[size * i] = '\0';
		}
		else 
		{
			ft_printf("%s\n", temp);
			free(str);
			return (0);
		}
	}
	err->code = 0;
	return (0);
}
