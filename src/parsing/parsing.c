/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:08:44 by cassie            #+#    #+#             */
/*   Updated: 2024/03/05 13:17:15 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_parsing(t_cmd **cmd, char *line, t_list **env, t_error *err)
{
	char	*line_temp;
	char	**line_tab;
	int		i;

	i = 0;
	(void)cmd;
	line_temp  = clean_line(line);
	line_temp = add_space_chevron(line_temp);
	line_temp = check_dollars(line_temp, env, err);
	line_tab = split_pipe(line_temp);
	while (line_tab[i])
	{
		line_to_cmd(cmd, line_tab[i], env);
		i++;
	}
	clean_quote(cmd);
	free(line_tab);
	ft_cmd_print(cmd);
}
