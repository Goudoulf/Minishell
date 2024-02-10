/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:56:38 by cassie            #+#    #+#             */
/*   Updated: 2023/11/22 15:36:58 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*big1;
	char	*little1;
	size_t	i;
	size_t	j;
	int		k;

	i = 0;
	big1 = (char *)big;
	little1 = (char *)little;
	if (little1[i] == '\0')
		return (big1);
	while ((i <= len) && (big1[i]))
	{
		j = i;
		k = 0;
		while ((big1[j] == little1[k]) && (j < len))
		{
			if ((little[k + 1] == '\0'))
				return (&big1[i]);
			j++;
			k++;
		}
		i++;
	}
	return (NULL);
}
