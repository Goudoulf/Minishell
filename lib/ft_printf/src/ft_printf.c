/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:15:55 by cassie            #+#    #+#             */
/*   Updated: 2023/12/10 09:48:12 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_arg(const char *s, va_list args, int i)
{
	if (s[i + 1] == 'c')
		return (ft_printf_putchar(va_arg(args, int)));
	if (s[i + 1] == 's')
		return (ft_printf_putstr(va_arg(args, char *)));
	if (s[i + 1] == '%')
		return (ft_printf_putchar('%'));
	if (s[i + 1] == 'p')
		return (ft_printf_hexa_ptr((long unsigned int)va_arg(args, void *)));
	if (s[i + 1] == 'd' || s[i + 1] == 'i')
		return (ft_printf_putnbr(va_arg(args, int)));
	if (s[i + 1] == 'u')
		return (ft_unsigned_putnbr(va_arg(args, unsigned int)));
	if (s[i + 1] == 'x')
		return (ft_printf_hexa((unsigned int)va_arg(args, int), 'x'));
	if (s[i + 1] == 'X')
		return (ft_printf_hexa((unsigned int)va_arg(args, int), 'X'));
	return (0);
}

static int	ft_check_arg(const char *s, va_list args, size_t i)
{
	int	j;
	int	size;

	j = 0;
	while (i < ft_printf_strlen(s))
	{
		if (s[i] != '%')
		{
			size = ft_printf_putchar(s[i]);
			if (size == -1)
				return (-1);
			j = j + size;
		}
		else
		{
			size = ft_print_arg(s, args, i);
			if (size == -1)
				return (-1);
			j = j + size;
			i++;
		}
		i++;
	}
	return (j);
}

int	ft_printf(const char *s, ...)
{
	size_t			i;
	unsigned int	j;
	va_list			args;

	i = 0;
	j = 0;
	if (!s[i])
		return (0);
	va_start(args, s);
	j = ft_check_arg(s, args, i);
	va_end(args);
	return (j);
}
