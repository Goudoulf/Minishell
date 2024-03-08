/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:12:35 by cassie            #+#    #+#             */
/*   Updated: 2024/03/03 10:03:30 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tab(char **tab)
{
	if (!tab)
		return ;
	while (*tab)
	{
		free(*tab);
		tab++;
	}
}

static char	*check_path(char **paths, char *arg)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	if (!paths || !arg)
		return (NULL);
	if (access(arg, X_OK) == 0)
		return (ft_strdup(arg));
	while (paths[i])
	{
		cmd = ft_join(paths[i], arg);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char *path)
{
	char	**paths;
	char	*new_path;

	paths = ft_split(path, ':');
	new_path = check_path(paths, cmd);
	if (paths)
	{
		free_tab(paths);
		free(paths);
	}
	return (new_path);
}
