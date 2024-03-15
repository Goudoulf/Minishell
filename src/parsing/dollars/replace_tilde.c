/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_tilde.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:17:27 by cassie            #+#    #+#             */
/*   Updated: 2024/03/15 16:46:45 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_temp(char *s2, char *s3, char *s4)
{
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
}

static char	*env_replace(char *temp, t_list *env_m)
{
	if (env_m)
	{
		temp = ft_strdup(env_m->var_content);
		return (temp);
	}
	return (ft_strdup("\0"));
}

char	*replace_tilde(char *line, t_list **env, int start)
{
	t_list	*env_match;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp3 = NULL;
	start = start_tilde(line, start);
	temp1 = ft_substr(line, 0, start);
	temp2 = ft_substr(line, start + 1, ft_strlen(line));
	env_match = check_cmd_env("HOME", env);
	temp3 = env_replace(temp3, env_match);
	free(line);
	line = ft_strjoin(temp1, temp3);
	free(temp1);
	temp1 = ft_strjoin(line, temp2);
	free_temp(temp2, temp3, line);
	return (temp1);
}
