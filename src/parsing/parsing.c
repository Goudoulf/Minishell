/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:08:44 by cassie            #+#    #+#             */
/*   Updated: 2024/02/24 10:27:01 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_parsing(t_cmd **cmd, char *line)
{
	char	*line_temp;
	char	**line_tab;

	(void)cmd;
	line_temp  = clean_line(line);
	line_tab = split_pipe(line_temp);
	while (*line_tab)
	{
		line_to_cmd(cmd, *line_tab);
		line_tab++;
	}
	ft_cmd_print(cmd);
	//check content of each block and put it in linked list
}
