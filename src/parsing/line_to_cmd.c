/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:31:34 by cassie            #+#    #+#             */
/*   Updated: 2024/03/12 16:24:32 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_to_cmd(t_cmd **cmd, char *line)
{
	char	**command;
	char	**redirection;
	char	*token;
	int		i;
	int		k;

	i = 0;
	k = 0;
	redirection = create_tab(in_count(line) + out_count(line));
	command = create_tab(cmd_count(line) - in_count(line) - out_count(line));
	token = ft_strtok_quote(line, " ");
	while (token)
	{
		if (!token)
			break;
		else if (token[0] == '<' || token[0] == '>')
			redirection[i++] = ft_strdup(token);
		else if (token)
			command[k++] = ft_strdup(token);
		token = ft_strtok_quote(NULL, " ");
	}
	free(line);
	ft_cmdadd_back(cmd, ft_cmd_new(command, redirection));
}
