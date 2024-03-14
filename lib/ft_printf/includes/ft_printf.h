/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:15:06 by cassie            #+#    #+#             */
/*   Updated: 2024/01/21 18:51:43 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

int		ft_printf(int fd, const char *s, ...);
int		ft_unsigned_putnbr(unsigned int n, int fd);
int		ft_printf_hexa(unsigned int n, char c, int fd);
int		ft_printf_hexa_ptr(long unsigned int n, int fd);
int		ft_printf_putchar(char c, int fd);
int		ft_printf_putnbr(int n, int fd);
int		ft_printf_putstr(char *s, int fd);
size_t	ft_printf_strlen(const char *s);

#endif
