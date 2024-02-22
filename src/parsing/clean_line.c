/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:55:53 by cassie            #+#    #+#             */
/*   Updated: 2024/02/22 13:19:09 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	ft_iswhite_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' ||
		c == '\f' || c== '\r')
		return (1);
	else
		return (0);
}*/

static int	ft_is_chevron(int c)
{
	if (c == '<' || c == '>')
		return (1);
	else
		return (0);
}

static size_t	chevron_space_size(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_is_chevron(str[i]))
		{
			if (str[i + 1] == ' ')
				i++;
			else if (ft_is_chevron(str[i]))
			{
				if (str[i + 1] == ' ')
					i++;
			}
		}
		i++;
		j++;
	}
	return (j);
}

static char	*clean_space(char *line)
{
	char	*temp;
	size_t	new_size;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	temp = NULL;
	if (!line)
		return (NULL);
	new_size = chevron_space_size(line);
	temp = malloc(sizeof(char) * new_size + 1);
	if (!temp)
		return (NULL);
	while (i <= new_size)
	{
		temp[j] = line[i];
		if (ft_is_chevron(line[i]))
		{
			if (line[i + 1] == ' ')
				i++;
			else if (ft_is_chevron(line[i]))
			{
				if (line[i + 1] == ' ')
					i++;
			}
		}
		i++;
		j++;
	}
	temp[j] = '\0';
	//free(line);
	return (temp);
}

char	*clean_line(char *line)
{
	char *temp_line;

	temp_line = clean_space(line);
	printf("%s\n", temp_line);
	return (temp_line);
}
