/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_out_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:40:57 by cassie            #+#    #+#             */
/*   Updated: 2024/03/15 22:42:04 by cassie           ###   ########.fr       */
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
	token = ft_strtok_quote(str, "\t ");
	while (token)
	{
		count++;
		token = ft_strtok_quote(NULL, "\t ");
	}
	free(str);
	return (count);
}

size_t	in_count(char *line)
{
	size_t	i;
	size_t	count;
	char	c_quote;
	bool	quote;

	i = 0;
	count = 0;
	c_quote = 0;
	quote = false;
	while (line[i])
	{
		if (quote == false && (line[i] == '\"' || line[i] == '\''))
			set_quote(&quote, &c_quote, line[i]);
		else if (quote == true && line[i] == c_quote)
			set_quote(&quote, &c_quote, line[i]);
		if (!c_quote && line[i] == '<' && line[i + 1] != '<')
			count++;
		i++;
	}
	return (count);
}

size_t	out_count(char *line)
{
	size_t	i;
	size_t	count;
	char	c_quote;
	bool	quote;

	i = 0;
	count = 0;
	c_quote = 0;
	quote = false;
	while (line[i])
	{
		if (quote == false && (line[i] == '\"' || line[i] == '\''))
			set_quote(&quote, &c_quote, line[i]);
		else if (quote == true && line[i] == c_quote)
			set_quote(&quote, &c_quote, line[i]);
		if (!c_quote && line[i] == '>' && line[i + 1] != '>')
			count++;
		i++;
	}
	return (count);
}
