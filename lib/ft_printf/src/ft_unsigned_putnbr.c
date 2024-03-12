/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_putnbr_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:17:13 by cassie            #+#    #+#             */
/*   Updated: 2023/11/30 14:07:00 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_int_len3(unsigned int nb)
{
	unsigned int	y;

	y = 1;
	while (nb / 10 != 0)
	{
		y = y * 10;
		nb = nb / 10;
	}
	return (y);
}

int	ft_unsigned_putnbr(unsigned int n, int fd)
{
	size_t	y;
	size_t	i;

	i = 0;
	if (n < 10)
		i = i + ft_printf_putchar((n + 48), fd);
	y = ft_int_len3(n);
	if (n >= 10)
	{
		while (y != 0)
		{
			i = i + ft_printf_putchar((n / y + 48), fd);
			n = n % y;
			y = y / 10;
		}
	}
	return (i);
}
