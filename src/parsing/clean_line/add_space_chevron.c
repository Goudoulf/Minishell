/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space_chevron.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 09:18:20 by cassie            #+#    #+#             */
/*   Updated: 2024/03/18 16:10:16 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// gerer size 0 ou null

static size_t	chevron_add_space_size(char *str, size_t i, size_t space)
{
	char	c_quote;

	c_quote = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\''))
		{
			c_quote = str[i++];
			while (str[i] && str[i] != c_quote)
				i++;
			if (str[i] == c_quote)
				i++;
			c_quote = 0;
			continue ;
		}
		if (!ft_is_space(str[i]) && !ft_is_chevron(str[i])
			&& ft_is_chevron(str[i + 1]))
			space++;
		i++;
	}
	return (i + space);
}

static char	*add_space(char *line, size_t i, size_t j, char c_quote)
{
	char	*temp;
	size_t	new_size;
	bool	quote;

	quote = false;
	new_size = chevron_add_space_size(line, 0, 0);
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
		if (!quote && !ft_is_space(line[i]) && !ft_is_chevron(line[i])
			&& ft_is_chevron(line[i + 1]))
			temp[++j] = ' ';
		i++;
		j++;
	}
	temp[j] = 0;
	return (temp);
}

char	*add_space_chevron(char *line)
{
	char	*temp_line;

	temp_line = add_space(line, 0, 0, 0);
	free(line);
	return (temp_line);
}
