/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:44:20 by cassie            #+#    #+#             */
/*   Updated: 2024/03/02 18:19:07 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_strcpy7(char *destination, const char *source, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
	return (*destination);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*temp;

	temp = NULL;
	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
	{
		temp = malloc(sizeof(char) * 1);
		if (!temp)
			return (NULL);
		ft_strcpy7(temp, "", 1);
		return (temp);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(&s[start]);
	if (s)
	{
		temp = malloc(sizeof(char) * len + 1);
		if (!temp)
			return (NULL);
		ft_strcpy7(temp, &s[start], len);
	}
	return (temp);
}
