/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:55:53 by cassie            #+#    #+#             */
/*   Updated: 2024/03/06 12:49:26 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// gerer size 0 ou null

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

static int	ft_is_chevron(int c)
{
	if (c == '<' || c == '>')
		return (1);
	else
		return (0);
}

static size_t	chevron_space_size(char *str, size_t i, size_t j, char c_quote)
{
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\''))
		{
			c_quote = str[i++];
			j++;
			while (str[i] && str[i] != c_quote)
			{
				i++;
				j++;
			}
			c_quote = 0;
		}
		else if (ft_is_chevron(str[i]))
		{
			while (str[i + 1] == ' ')
				i++;
		}
		i++;
		j++;
	}
	return (j);
}

static char	*clean_space(char *line, size_t i, size_t j, bool quote, char c_quote)
{
	char	*temp;
	size_t	new_size;

	new_size = chevron_space_size(line, 0, 0, 0);
	temp = malloc(sizeof(char) * new_size + 1);
	if (!temp)
		return (NULL);
	while (j < new_size)
	{
		if (quote == false && (line[i] == '\"' || line[i] == '\''))
			set_quote(&quote, &c_quote, line[i]);
		else if (quote == true && line[i] == c_quote)
			set_quote(&quote, &c_quote, line[i]);
		temp[j] = line[i];
		if (quote == false && ft_is_chevron(line[i]))
		{
			while (line[i + 1] == ' ')
				i++;
		}
		i++;
		j++;
	}
	temp[j] = 0;
	return (temp);
}

char	*clean_line(char *line)
{
	char *temp_line;

	temp_line = clean_space(line, 0, 0, 0, 0);
	return (temp_line);
}
