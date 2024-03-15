/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:11:29 by cassie            #+#    #+#             */
/*   Updated: 2024/03/15 16:38:38 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_loop(char *line, int i, char c_quote)
{
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && !c_quote)
			c_quote = line[i];
		else if (line[i] == c_quote)
			c_quote = 0;
		if (line[i] == '|' && line[i + 1] == '|' && !c_quote)
			return (stderr_c("syntax error near unexpected token `",
					line[i], "\'", -1));
		if (line[i] == '|' && line[i + 1] != '|' && !c_quote)
		{
			i++;
			while (ft_is_space(line[i]))
				i++;
			if (line[i] == '|' || line[i] == '\0')
				return (stderr_c("syntax error near unexpected token `",
						line[i], "\'", -1));
		}
		else
			i++;
	}
	return (i);
}

int	check_pipe(char *line)
{
	int		i;

	i = 0;
	while (ft_is_space(line[i]))
		i++;
	if (line[i] == '|')
		return (stderr_c("syntax error near unexpected token `", '|', "\'", 0));
	i = pipe_loop(line, i, 0);
	if (i == -1)
		return (0);
	return (1);
}
