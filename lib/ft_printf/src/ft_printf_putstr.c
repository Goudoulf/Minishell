/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:03:36 by cassie            #+#    #+#             */
/*   Updated: 2023/12/10 09:47:45 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_putstr(char *s)
{
	int	size;

	if (!s)
	{
		size = write(1, "(null)", 6);
		if (size == -1)
			return (-1);
		return (6);
	}
	size = write(1, s, ft_printf_strlen(s));
	if (size == -1)
		return (-1);
	return (ft_printf_strlen(s));
}
