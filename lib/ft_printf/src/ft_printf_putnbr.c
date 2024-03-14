/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:44:20 by cassie            #+#    #+#             */
/*   Updated: 2023/12/10 09:48:44 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static int	ft_printnbr(int nb, int y, int fd)
{
	int	size;
	int	i;

	i = 0;
	while (y != 0)
	{
		size = ft_printf_putchar((nb / y + 48), fd);
		if (size == -1)
			return (-1);
		i = i + size;
		nb = nb % y;
		y = y / 10;
	}
	return (i);
}

int	ft_printf_putnbr(int n, int fd)
{
	int	y;
	int	i;
	int	size;

	i = 0;
	if (n == -2147483648)
		return (ft_printf_putstr("-2147483648", fd));
	if (n < 0)
	{
		size = write(fd, "-", 1);
		if (size == -1)
			return (-1);
		n = n * -1;
		i++;
	}
	y = ft_int_len(n);
	size = ft_printnbr(n, y, fd);
	if (size == -1)
		return (-1);
	i = i + size;
	return (i);
}
