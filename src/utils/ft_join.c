/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:14:00 by cassie            #+#    #+#             */
/*   Updated: 2024/03/03 10:01:47 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	ft_strcpy(char *destination, const char *source)
{
	int	i;

	i = 0;
	while (source[i] && source[i] != ' ')
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
	return (*destination);
}

char	*ft_join(const char *s1, const char *s2)
{
	char	*temp;
	char	*slash;

	temp = NULL;
	slash = NULL;
	slash = malloc(sizeof(char) * 2);
	slash[0] = '/';
	slash[1] = '\0';
	if ((s1) && (s2))
	{
		temp = malloc((ft_strlen(s1) + 1) + (ft_strlen(s2) + 1));
		if (!temp)
			return (NULL);
		ft_strcpy(temp, s1);
		ft_strcpy(&temp[ft_strlen(s1)], slash);
		ft_strcpy(&temp[ft_strlen(s1) + 1], s2);
	}
	free(slash);
	return (temp);
}
