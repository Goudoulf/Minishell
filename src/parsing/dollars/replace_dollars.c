/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:11:15 by cassie            #+#    #+#             */
/*   Updated: 2024/03/19 15:59:46 by cassie           ###   ########.fr       */
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
	int	old_start;

	end = 0;
	old_start = start;
	start++;
	if (ft_isdigit(line[start]))
		return (end + 1);
	while (line[start] && !ft_is_end(line[start]))
	{
		start++;
		end++;
		if (start > old_start && line[start] == '?')
			break ;
	}
	return (end);
}

static char	*set_temp3(char *temp3, t_error *err)
{
	t_list	*env_match;

	env_match = check_cmd_env(temp3, err->env);
	temp3 = env_replace2(temp3, env_match, err);
	if (!temp3)
		return (NULL);
	return (temp3);
}

static char	*set_temp(char **line, int start, int end, t_error *err)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_substr(*line, 0, start);
	temp2 = ft_substr(*line, start + 1 + end, ft_strlen(*line));
	temp3 = ft_substr(*line, start + 1, end);
	free(*line);
	if (!temp1 || !temp2 || !temp3)
		quit_error(err);
	temp3 = set_temp3(temp3, err);
	*line = ft_strjoin(temp1, temp3);
	free_temp(temp1, temp3, NULL);
	if (!*line)
	{
		free(temp2);
		quit_error(err);
	}
	temp1 = ft_strjoin(*line, temp2);
	free_temp(*line, temp2, NULL);
	if (!temp1)
		quit_error(err);
	return (temp1);
}

char	*replace_dollar(char *line, t_list **env, int start, t_error *err)
{
	int		end;
	char	*new_line;

	(void)env;
	start = start_dollar(line, start);
	if ((ft_is_end(line[start + 1]) && !not_in_quote(line, start))
		|| line[start + 1] == '\0' || line[start + 1] == 47)
		return (line);
	end = end_dollar(line, start);
	new_line = set_temp(&line, start, end, err);
	return (new_line);
}
