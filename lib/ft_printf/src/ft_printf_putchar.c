/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putchar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:59:39 by cassie            #+#    #+#             */
/*   Updated: 2023/12/10 09:47:28 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_putchar(char c, int fd)
{
	int	size;

	size = write(fd, &c, 1);
	if (size == -1)
		return (-1);
	return (1);
}
