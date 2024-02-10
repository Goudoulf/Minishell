/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:44:20 by cassie            #+#    #+#             */
/*   Updated: 2023/11/22 20:29:03 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_l;

	j = 0;
	i = ft_strlen(dst);
	dest_l = i;
	if (i < size - 1 && size > 0)
	{
		while ((dest_l + j < size - 1) && (src[j]))
		{
			dst[i] = src[j];
			j++;
			i++;
		}
		dst[i] = '\0';
	}
	if (dest_l >= size)
		dest_l = size;
	return (dest_l + ft_strlen(src));
}
