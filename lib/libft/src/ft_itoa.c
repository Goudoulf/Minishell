/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:44:20 by cassie            #+#    #+#             */
/*   Updated: 2024/03/04 15:29:50 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_negative(int n)
{
	if (n >= 0)
		return (0);
	else
		return (1);
}

static char	*ft_strlcpy2(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while ((i < size))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static int	ft_int_len2(int nb)
{
	int	y;

	y = 1;
	if ((nb >= -9) && (nb <= 9))
		return (1);
	while (nb / 10 != 0)
	{
		y++;
		nb = nb / 10;
	}
	return (y);
}

static int	ft_int_len(int nb)
{
	int	y;

	y = 1;
	while (nb / 10 != 0)
	{
		y = y * 10;
		nb = nb / 10;
	}
	return (y);
}

char	*ft_itoa(int n)
{
	int		y;
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_int_len2(n) + ft_negative(n) + 1));
	if (!str)
		return (NULL);
	if (n == -2147483648)
		return (ft_strlcpy2(str, "-2147483648", 11));
	if (n < 0)
	{
		str[i++] = '-';
		n = n * -1;
	}
	y = ft_int_len(n);
	while (y != 0)
	{
		str[i++] = (n / y + 48);
		n = n % y;
		y = y / 10;
	}
	str[i] = '\0';
	return (str);
}
