/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:08:44 by cassie            #+#    #+#             */
/*   Updated: 2024/03/11 12:02:25 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_parsing(t_cmd **cmd, char *line, t_list **env, t_error *err)
{
	char	*line_temp;
	char	**line_tab;
	int		i;

	i = 0;
	line_temp  = del_space_chevron(line);
	line_temp = add_space_chevron(line_temp);
	line_temp = check_dollars(line_temp, env, err);
	line_temp = check_tilde(line_temp, env);
	line_tab = split_pipe(line_temp);
	while (line_tab[i])
	{
		line_to_cmd(cmd, line_tab[i]);
		i++;
	}
	clean_quote(cmd);
	clean_redirection(cmd);
	cmd_add_path(cmd, env);
	free(line_tab);
//	ft_cmd_print(cmd);
}
