/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_any.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 09:53:07 by cassie            #+#    #+#             */
/*   Updated: 2024/03/10 17:39:40 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_chevron(int c)
{
	if (c == '<' || c == '>')
		return (1);
	else
		return (0);
}

int	ft_is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

int	ft_is_end(int c)
{
	if (c == ' ' || c == '\t' || c == '\'' || c == '\"' || c == '|'
		|| c == '\0' || c == '$' || c == '=')
		return (1);
	else
		return (0);
}
