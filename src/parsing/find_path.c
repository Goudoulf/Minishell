/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:12:35 by cassie            #+#    #+#             */
/*   Updated: 2024/03/14 14:03:22 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_path(char **paths, char *arg)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	if (!arg)
		return (NULL);
	if (access(arg, X_OK) == 0)
		return (ft_strdup(arg));
	if (!paths)
		return (NULL);
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

char	*find_path(char *cmd, char *path, char *pwd)
{
	char	**paths;
	char	*new_path;

	if (!path)
	{
		paths = malloc(sizeof (char *) * 2);
		paths[0] = ft_strdup(pwd);
		paths[1] = NULL;
	}
	else
		paths = ft_split(path, ':');
	new_path = check_path(paths, cmd);
	if (paths)
	{
		free_tab(paths);
		free(paths);
	}
	return (new_path);
}
