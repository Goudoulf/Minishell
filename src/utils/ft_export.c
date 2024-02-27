/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 08:31:17 by cassie            #+#    #+#             */
/*   Updated: 2024/02/19 12:42:07 by cassie           ###   ########.fr       */
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

static void	env_print_declare(**tab)
{
	int	i;

	i = 0;
	while (tab[i])
		ft_printf("declare -x %s\n", tab[i++]);

}

static char	**env_add(t_data **data, char *arg)
{
	size_t	size;

	size = env_size(data->env);
}

int	ft_export(t_data **data, char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (envp_print_declare(data->env), 1);
}
