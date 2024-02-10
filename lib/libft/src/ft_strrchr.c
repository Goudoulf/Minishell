/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:44:20 by cassie            #+#    #+#             */
/*   Updated: 2023/11/22 20:29:21 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	len;

	str = (char *) s;
	len = ft_strlen(str);
	while (len != 0)
	{
		if (s[len] == (char)c)
			return (&str[len]);
		len--;
	}
	if (s[len] == (char)c)
		return (&str[len]);
	return (NULL);
}
