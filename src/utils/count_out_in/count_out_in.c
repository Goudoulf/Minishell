/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_out_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:40:57 by cassie            #+#    #+#             */
/*   Updated: 2024/03/09 08:42:15 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	cmd_count(char *s)
{
	char	*token;
	char	*str;
	size_t	count;

	count = 0;
	str = ft_strdup(s);
	token = ft_strtok_quote(str, " ");
	while (token)
	{
		count++;
		token = ft_strtok_quote(NULL, " ");
	}
	free(str);
	return (count);
}

size_t in_count(char *line)
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

size_t out_count(char *line)
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

