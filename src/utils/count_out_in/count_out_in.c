/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_out_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:40:57 by cassie            #+#    #+#             */
/*   Updated: 2024/02/25 18:41:58 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	cmd_count(char const *s, char c)
{
	int	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
		if (s[i])
			i++;
	}
	return (count);
}

size_t infile_count(char *line)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while(line[i])
	{
		if (line[i] == '<' && line[i + 1] != '<')
			count++;
		i++;
	}
	return (count);
}

size_t outfile_count(char *line)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while(line[i])
	{
		if (line[i] == '>' && line[i + 1] != '>')
			count++;
		i++;
	}
	return (count);
}

