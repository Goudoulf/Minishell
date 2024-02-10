/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:44:20 by cassie            #+#    #+#             */
/*   Updated: 2023/11/22 20:28:33 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_int_len3(int nb)
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

void	ft_putnbr_fd(int n, int fd )
{
	int	y;

	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
	}
	if (n < 10)
		ft_putchar((n + 48), fd);
	y = ft_int_len3(n);
	if (n >= 10)
	{
		while (y != 0)
		{
			ft_putchar((n / y + 48), fd);
			n = n % y;
			y = y / 10;
		}
	}
}
