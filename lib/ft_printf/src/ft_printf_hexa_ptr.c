/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:23:54 by cassie            #+#    #+#             */
/*   Updated: 2023/12/10 09:50:39 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_str(char *s, int fd)
{
	char	*front;
	int		size;

	front = "0x";
	size = ft_printf_putstr(front, fd);
	if (size == -1)
		return (-1);
	size = ft_printf_putstr(s, fd);
	if (size == -1)
		return (-1);
	return (2 + ft_printf_strlen(s));
}

static char	ft_dec_to_hex(unsigned long int nb)
{
	char	*str;

	str = "0123456789abcdef";
	return (str[nb]);
}

static int	ft_int_len3(unsigned long int nb)
{
	unsigned long int	y;

	y = 0;
	while (nb != 0)
	{
		y++;
		nb = nb / 16;
	}
	return (y);
}

int	ft_printf_hexa_ptr(long unsigned int n, int fd)
{
	unsigned long int		i;
	char					*str1;

	if (n == 0)
		return (ft_printf_putstr("(nil)", fd));
	i = ft_int_len3(n);
	str1 = malloc(sizeof(char) * (i + 1));
	if (!str1)
		return (0);
	str1[i] = '\0';
	i--;
	while (n > 0)
	{
		str1[i] = ft_dec_to_hex((n % 16));
		n = n / 16;
		i--;
	}
	i = ft_print_str(str1, fd);
	free(str1);
	return (i);
}
