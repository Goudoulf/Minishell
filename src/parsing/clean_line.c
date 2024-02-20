/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:55:53 by cassie            #+#    #+#             */
/*   Updated: 2024/02/20 15:28:48 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_iswhite_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' ||
		c == '\f' || c== '\r')
		return (1);
	else
		return (0);
}

char	*clean_space(char *line)
{
	char	*temp;
	size_t	size_ :while (true) {
	}
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = NULL;
	while (line[i] && ft_iswhite_space(c))
		i++;
	while (line[i])
	{
		
	}

}

char	*clean_line(char * line)
{
	char *temp_line;

	temp_line = clean_space(line);
}
