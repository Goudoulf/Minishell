/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:48:05 by cassie            #+#    #+#             */
/*   Updated: 2024/03/01 07:59:04 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_strcpy2(char *destination, const char *source)
{
	int	i;

	i = 0;
	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
	return (*destination);
}

char	*ft_strdup(const char *s)
{
	char	*temp;

	if (!s)
		return (NULL);
	temp = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!temp)
		return (NULL);
	ft_strcpy2(temp, s);
	return (temp);
}
