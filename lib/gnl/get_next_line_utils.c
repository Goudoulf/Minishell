/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:35:04 by rjacq             #+#    #+#             */
/*   Updated: 2024/03/12 14:45:37 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_realloc(char *p1, char *p2, size_t msize)
{
	size_t	i;
	size_t	j;
	char	*dst;

	i = 0;
	j = 0;
	dst = malloc(sizeof (char) * (msize + 1));
	if (!dst)
		return (free(p1), NULL);
	dst[msize] = '\0';
	if (p1)
	{
		while (p1[i])
		{
			dst[i] = p1[i];
			i++;
		}
	}
	while (i + j < msize)
	{
		dst[i + j] = p2[j];
		j++;
	}
	free(p1);
	return (dst);
}

void	ft_substr2(char *dst, size_t len)
{
	size_t	i;

	i = 0;
	while (len + i < BUFFER_SIZE)
	{
		dst[i] = dst[i + len];
		i++;
	}
	while (i < BUFFER_SIZE)
		dst[i++] = '\0';
}
