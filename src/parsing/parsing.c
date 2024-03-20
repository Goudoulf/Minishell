/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:08:44 by cassie            #+#    #+#             */
/*   Updated: 2024/03/20 10:00:49 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_dollars(t_cmd **cmd, t_list **env, t_error *err, int i)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		i = -1;
		while (temp->cmd && temp->cmd[++i])
			temp->cmd[i] = check_dollars(temp->cmd[i], env, err);
		i = -1;
		while (temp->redirection && temp->redirection[++i])
		{
			if (ft_strncmp(temp->redirection[i], "<<", 2))
				temp->redirection[i] = check_dollars(temp->redirection[i],
						env, err);
		}
		i = -1;
		while (temp->here_doc && temp->here_doc[++i])
			temp->here_doc[i] = check_dollars(temp->here_doc[i], env, err);
		temp = temp->next;
	}
}

static void	final_clean(t_cmd **cmd, t_list **env, t_error *err)
{
	cmd_dollars(cmd, env, err, -1);
	clean_quote(cmd, err);
	clean_redirection(cmd, err);
	cmd_add_path(cmd, env);
}

void	line_parsing(t_cmd **cmd, char *line, t_list **env, t_error *err)
{
	char	*line_temp;
	char	**line_tab;
	int		i;

	i = 0;
	line_temp = del_space_chevron(line, err);
	line_temp = add_space_chevron(line_temp, err);
	line_temp = check_tilde(line_temp, env, err);
	line_tab = split_pipe(line_temp, err);
	while (line_tab && line_tab[i])
	{
		line_temp = line_to_cmd(cmd, line_tab[i], err, NULL);
		if (line_temp)
		{
			line_temp = check_dollars(line_temp, env, err);
			line_to_cmd2(cmd, line_temp, err);
		}
		i++;
	}
	if (line_tab)
	{
		final_clean(cmd, env, err);
		free(line_tab);
	}
}
