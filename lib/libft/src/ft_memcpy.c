/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:20:11 by cassie            #+#    #+#             */
/*   Updated: 2023/11/22 15:37:54 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*strd;
	const char	*strs;

	if (!dest && !src)
		return (NULL);
	strs = src;
	i = 0;
	strd = dest;
	while (i < n)
	{
		strd[i] = strs[i];
		i++;
	}
	return (dest);
}
