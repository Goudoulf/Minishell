/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:08:44 by cassie            #+#    #+#             */
/*   Updated: 2024/02/22 10:43:15 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_parsing(t_cmd **cmd, char *line)
{
	(void)cmd;
	clean_line(line);
	//clean string line : remove unnessary space "" and ''
	//split line in block at each pipe
	//check content of each block and put it in linked list
}
