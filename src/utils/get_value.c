/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:22:41 by cassie            #+#    #+#             */
/*   Updated: 2024/02/28 12:44:04 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(t_list **env, char *s)
{
	t_list	*temp;

	if (!env)
		return (NULL);
	temp = *env;
	while (temp)
	{
		if (!ft_strncmp(temp->var, s, ft_strlen(temp->var)))
			return (temp->var_content);
		temp = temp->next;
	}
	return (NULL);
}
