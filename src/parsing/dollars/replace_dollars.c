/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:11:15 by cassie            #+#    #+#             */
/*   Updated: 2024/03/11 13:09:41 by cassie           ###   ########.fr       */
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

static int	end_dollar(char *line, int start)
{
	int	end;

	end = 0;
	start++;
	if (ft_isdigit(line[start]))
		return (end + 1);
	while (line[start] && !ft_is_end(line[start]))
	{
		start++;
		end++;
	}
	return (end);
}

static char *env_replace(char *temp, t_list *env_m, t_error *err)
{
	if (!env_m && !ft_strncmp("?", temp, ft_strlen(temp)))
	{
		free(temp);
		temp = ft_itoa(err->code);
		return (temp);
	}
	else if (!env_m)
	{
		free(temp);
		temp = ft_strdup("\0");
		return (temp);
	}
	else
	{
		free(temp);
		temp = ft_strdup(env_m->var_content);
		return (temp);
	}
}

char *replace_dollar(char *line, t_list **env, int start, t_error *err)
{
	t_list *env_match;
	char *temp1;
	char *temp2;
	char *temp3;
	int	end;

	start = start_dollar(line, start);
	if (ft_is_end(line[start + 1]))
		return (line);
	end = end_dollar(line, start);
	temp1 = ft_substr(line, 0, start);
	temp2 = ft_substr(line, start + 1 + end, ft_strlen(line));
	temp3 = ft_substr(line, start + 1, end);
	env_match = check_cmd_env(temp3, env);
	temp3 = env_replace(temp3, env_match, err);
	free(line);
	line = ft_strjoin(temp1, temp3);
	free(temp1);
	temp1 = ft_strjoin(line, temp2);
	free_temp(temp2, temp3, line);
	return (temp1);
}
