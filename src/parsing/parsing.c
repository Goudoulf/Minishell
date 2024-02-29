/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:08:44 by cassie            #+#    #+#             */
/*   Updated: 2024/02/29 18:17:46 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_parsing(t_cmd **cmd, char *line, t_list **env)
{
	char	*line_temp;
	char	**line_tab;
	int		i;

	i = 0;
	(void)cmd;
	line_temp  = clean_line(line);
	line_tab = split_pipe(line_temp);
	while (line_tab[i])
	{
		line_to_cmd(cmd, line_tab[i], env);
		i++;
	}
	free(line_tab);
	ft_cmd_print(cmd);
}
