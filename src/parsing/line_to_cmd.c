/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:31:34 by cassie            #+#    #+#             */
/*   Updated: 2024/03/20 07:56:07 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	ft_strcpy5(char *destination, const char *source)
{
	int	i;

	i = 0;
	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
	return (*destination);
}

static char	*ft_strjoin2(char *s1, char *s2)
{
	char	*temp;

	temp = NULL;
	if ((s1) && (s2))
	{
		temp = malloc((ft_strlen(s1)) + (ft_strlen(s2) + 2));
		if (!temp)
			return (NULL);
		ft_strcpy5(temp, s1);
		temp[ft_strlen(s1)] = ' ';
		ft_strcpy5(&temp[ft_strlen(s1) + 1], s2);
		free(s1);
		free(s2);
		s1 = NULL;
	}
	return (temp);
}

static int	tok_cmd(char **token, char **redirection, char **new_line)
{
	while (*token)
	{
		if (*token[0] == '<' || *token[0] == '>')
		{
			*redirection = ft_strdup(*token);
			if (!*redirection)
				return (0);
			redirection++;
		}
		else if (*token && *new_line)
		{
			*new_line = ft_strjoin2(*new_line, ft_strdup(*token));
			if (!new_line)
				return (0);
		}
		else if (*token)
		{
			*new_line = ft_strdup(*token);
			if (!new_line)
				return (0);
		}
		*token = ft_strtok_quote(NULL, "\t ");
	}
	return (1);
}

char	*line_to_cmd(t_cmd **cmd, char *line, t_error *err, char *new_line)
{
	char	**redirection;
	char	*token;
	size_t	count;

	count = in_count(line) + out_count(line);
	redirection = create_tab(count);
	if (!redirection && count > 0)
	{
		free(line);
		quit_error(err);
	}
	token = ft_strtok_quote(line, "\t ");
	if (!tok_cmd(&token, redirection, &new_line))
	{
		free(line);
		free_tab(redirection);
		free(redirection);
		quit_error(err);
	}
	free(line);
	ft_cmdadd_back(cmd, ft_cmd_new(redirection));
	return (new_line);
}
