/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:31:28 by cassie            #+#    #+#             */
/*   Updated: 2024/03/20 08:05:26 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*last_cmd(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

static void	tok_cmd2(char **token, char **command, char **line, t_error *err)
{
	int	k;

	k = 0;
	while (*token)
	{
		command[k] = ft_strdup(*token);
		if (!command[k])
		{
			free(*line);
			free_tab(command);
			free(command);
			quit_error(err);
		}
		k++;
		*token = ft_strtok_quote(NULL, "\t ");
	}
}

void	line_to_cmd2(t_cmd **cmd, char *line, t_error *err)
{
	char	**command;
	char	*token;
	t_cmd	*temp;
	size_t	count;

	temp = last_cmd(cmd);
	count = cmd_count(line);
	command = create_tab(count);
	if (!command && count > 0)
	{
		free(line);
		quit_error(err);
	}
	token = ft_strtok_quote(line, "\t ");
	tok_cmd2(&token, command, &line, err);
	temp->cmd = command;
	free(line);
}
