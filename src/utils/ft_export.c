/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 08:31:17 by cassie            #+#    #+#             */
/*   Updated: 2024/02/28 15:42:56 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t env_size(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static void	env_print(t_list **env, int fd)
{
	t_list *temp;

	temp = *env;

	while (temp)
	{
		ft_putstr_fd(temp->string, fd);
		ft_putstr_fd("\n", fd);
		temp = temp->next;
	}

}

static char	**env_add(t_data **data, char *arg)
{
	size_t	size;

	size = env_size(data->env);
}

int	ft_export(t_list **env, char **cmd, int	fd)
{
	int	i;

	i = 0;
	if (tab_size(cmd) == 1)
		return (envp_print(data->env), fd);
	
}
