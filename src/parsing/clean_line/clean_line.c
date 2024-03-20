/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:55:53 by cassie            #+#    #+#             */
/*   Updated: 2024/03/20 07:48:24 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// gerer size 0 ou null

static size_t	chevron_space_size(char *str, size_t i, size_t j, char c_quote)
{
	while (str && i < ft_strlen(str))
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
			if (!ft_is_chevron(str[i]) && ft_is_chevron(str[i + 1]))
				i--;
		}
		i++;
		j++;
	}
	return (j);
}

static char	*clean_space(char *line, size_t i, size_t j, char c_quote)
{
	char	*temp;
	size_t	new_size;

	new_size = chevron_space_size(line, 0, 0, 0);
	temp = malloc(sizeof(char) * new_size + 1);
	if (!temp)
		return (NULL);
	while (j < new_size)
	{
		if (!c_quote && (line[i] == '\"' || line[i] == '\''))
			c_quote = line[i];
		else if (line[i] == c_quote)
			c_quote = 0;
		temp[j] = line[i];
		if (!c_quote && ft_is_chevron(line[i]) && !ft_is_chevron(line[i + 1]))
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

char	*del_space_chevron(char *line, t_error *err)
{
	char	*temp_line;

	temp_line = clean_space(line, 0, 0, 0);
	if (!temp_line)
		quit_error(err);
	return (temp_line);
}
