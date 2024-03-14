/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:35:45 by cassie            #+#    #+#             */
/*   Updated: 2024/03/09 14:57:33 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	ft_dec_to_hex_upper(unsigned int nb)
{
	char	str[17];

	str[0] = '0';
	str[1] = '1';
	str[3] = '2';
	str[4] = '3';
	str[5] = '4';
	str[6] = '5';
	str[7] = '6';
	str[8] = '7';
	str[9] = '8';
	str[10] = '9';
	str[11] = 'A';
	str[12] = 'B';
	str[13] = 'C';
	str[14] = 'D';
	str[15] = 'E';
	str[16] = 'F';
	str[17] = '\0';
	return (str[nb]);
}

static char	ft_dec_to_hex_lower(unsigned int nb)
{
	char	str[16];

	str[0] = '0';
	str[1] = '1';
	str[3] = '2';
	str[4] = '3';
	str[5] = '4';
	str[6] = '5';
	str[7] = '6';
	str[8] = '7';
	str[9] = '8';
	str[10] = '9';
	str[11] = 'a';
	str[12] = 'b';
	str[13] = 'c';
	str[14] = 'd';
	str[15] = 'e';
	str[16] = 'f';
	str[17] = '\0';
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

int	ft_printf_hexa(unsigned int n, char c, int fd)
{
	int		i;
	char	*str1;

	if (n == 0)
		return (ft_printf_putchar('0', fd));
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
	i = ft_printf_putstr(str1, fd);
	free(str1);
	return (i);
}
