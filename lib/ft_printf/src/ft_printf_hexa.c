/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:35:45 by cassie            #+#    #+#             */
/*   Updated: 2023/12/10 09:39:19 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	ft_dec_to_hex_upper(unsigned int nb)
{
	char	*str;

	str = "0123456789ABCDEF";
	return (str[nb]);
}

static char	ft_dec_to_hex_lower(unsigned int nb)
{
	char	*str;

	str = "0123456789abcdef";
	return (str[nb]);
}

static int	ft_int_len(unsigned int nb)
{
	size_t	i;

	i = 0;
	while (nb != 0)
	{
		i++;
		nb = nb / 16;
	}
	return (i);
}

int	ft_printf_hexa(unsigned int n, char c)
{
	int		i;
	char	*str1;

	if (n == 0)
		return (ft_printf_putchar('0'));
	i = ft_int_len(n);
	str1 = malloc(sizeof(char) * (i + 1));
	if (!str1)
		return (0);
	str1[i] = '\0';
	i--;
	while (n > 0)
	{
		if (c == 'x')
			str1[i] = ft_dec_to_hex_lower(n % 16);
		if (c == 'X')
			str1[i] = ft_dec_to_hex_upper(n % 16);
		n = n / 16;
		i--;
	}
	i = ft_printf_putstr(str1);
	free(str1);
	return (i);
}
