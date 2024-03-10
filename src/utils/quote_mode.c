/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:23:00 by cassie            #+#    #+#             */
/*   Updated: 2024/03/09 10:23:35 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_mode(char *c_quote, char char_line)
{
	if (!(*c_quote))
	{
		*c_quote = char_line;
	}
	else if ((*c_quote) && *c_quote == char_line)
		*c_quote = 0;
}
