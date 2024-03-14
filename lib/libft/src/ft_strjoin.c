/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:44:20 by cassie            #+#    #+#             */
/*   Updated: 2024/03/14 13:25:18 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_strcpy5(char *destination, const char *source)
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

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*temp;

	temp = NULL;
	if ((s1) && (s2))
	{
		temp = malloc((ft_strlen(s1)) + (ft_strlen(s2) + 1));
		if (!temp)
			return (NULL);
		ft_strcpy5(temp, s1);
		ft_strcpy5(&temp[ft_strlen(s1)], s2);
	}
	return (temp);
}
