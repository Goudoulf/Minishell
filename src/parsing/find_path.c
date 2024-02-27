/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:12:35 by cassie            #+#    #+#             */
/*   Updated: 2024/02/27 16:23:53 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	paths = NULL;
	paths = ft_split(path, ':');

	path = check_path(paths, cmd);
	return (path);
}
