/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_out_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:40:57 by cassie            #+#    #+#             */
/*   Updated: 2024/03/12 16:28:50 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_quote(bool *quote, char *c_quote, char char_line)
{
	if (*quote == false)
	{
		*quote = true;
		*c_quote = char_line;
	}
	else
	{
		*quote = false;
		*c_quote = 0;
	}
}

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
	char	c_quote;
	bool	quote;

	i = 0;
	count = 0;
	c_quote = 0;
	quote = false;
	while(line[i])
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

size_t out_count(char *line)
{
	size_t	i;
	size_t	count;
	char	c_quote;
	bool	quote;

	i = 0;
	count = 0;
	c_quote = 0;
	quote = false;
	while(line[i])
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

