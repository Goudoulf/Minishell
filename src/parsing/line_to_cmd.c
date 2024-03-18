/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:31:34 by cassie            #+#    #+#             */
/*   Updated: 2024/03/18 17:12:36 by cassie           ###   ########.fr       */
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

static t_cmd	*last_cmd(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	line_to_cmd2(t_cmd **cmd, char *line)
{
	char	**command;
	char	*token;
	t_cmd	*temp;
	int		k;

	k = 0;
	temp = last_cmd(cmd);
	command = create_tab(cmd_count(line));
	token = ft_strtok_quote(line, "\t ");
	while (token)
	{
		if (!token)
			break ;
		else if (token)
			command[k++] = ft_strdup(token);
		token = ft_strtok_quote(NULL, "\t ");
	}
	temp->cmd = command;
	free(line);
}

char	*line_to_cmd(t_cmd **cmd, char *line, int i, char *new_line)
{
	char	**redirection;
	char	*token;
	size_t	count;

	count = in_count(line) + out_count(line);
	redirection = create_tab(count);
	if (!redirection && count > 0)
		return (free(line), NULL);
	token = ft_strtok_quote(line, "\t ");
	while (token)
	{
		if (!token)
			break ;
		else if (token[0] == '<' || token[0] == '>')
			redirection[i++] = ft_strdup(token);
		else if (token && new_line)
			new_line = ft_strjoin2(new_line, ft_strdup(token));
		else if (token)
			new_line = ft_strdup(token);
		token = ft_strtok_quote(NULL, "\t ");
	}
	free(line);
	ft_cmdadd_back(cmd, ft_cmd_new(redirection));
	return (new_line);
}
