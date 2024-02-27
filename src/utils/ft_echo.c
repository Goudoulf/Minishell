/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:21:43 by cassie            #+#    #+#             */
/*   Updated: 2024/02/21 13:22:52 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *clear_str(char *str)
{
	int	i;
	int	k;
	int	j;
	char *temp;

	i = 0;
	j = 0;
	k = 0;
	temp = NULL;
	while (str[i] != '$')
		i++;
	i++;
	k = i;
	while (str[i] && str[i] != ' ')
	{
		i++;
		j++;
	}
	temp = ft_substr(str, k, j);
	return (temp);
}

static void	check_env(char *str, t_list **env)
{
	char *temp;
	t_list *env_cpy;
	size_t	len;
	size_t	len_cmp;

	env_cpy = *env;
	temp = clear_str(str);
	if (!temp || !*temp)
		ft_printf("$");
	len = ft_strlen(temp);
	len_cmp = 0;
	while (env_cpy != NULL && temp)
	{
		if (len >= ft_strlen(env_cpy->var))
			len_cmp = len;
		else
			len_cmp = ft_strlen(env_cpy->var);
		if (!ft_strncmp(temp, env_cpy->var, len_cmp))
		{
			ft_printf("%s", env_cpy->var_content);
			break ;
		}
		env_cpy = env_cpy->next;
	}
	free(temp);
}

int	ft_echo(char *str, char *arg, t_list **env)
{
	if (ft_strchr(str, '$'))
		check_env(str, env);
	else if (str)
		write(1, str, ft_strlen(str));
	if (!arg)
		write(1, "\n", 1);
	return (1);
}
