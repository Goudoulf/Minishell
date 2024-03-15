/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:34:15 by cassie            #+#    #+#             */
/*   Updated: 2024/03/15 15:35:00 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stderr_c(const char *str1, const char c, const char *str3, int ret)
{
	write(2, "minishell: ", 11);
	write(2, str1, ft_strlen(str1));
	if (c == '\0')
		write(2, "newline", 7);
	else
		write(2, &c, 1);
	write(2, str3, ft_strlen(str3));
	write(2, "\n", 1);
	return (ret);
}

