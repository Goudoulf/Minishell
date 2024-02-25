/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:48:16 by cassie            #+#    #+#             */
/*   Updated: 2024/02/25 19:37:21 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*str_from_char(char *str)
{
	int	i;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	if (str[i] == '=' && !str[i + 1])
		return (NULL);
	return(ft_substr(str, i + 1, ft_strlen(str)));
}

static char	*str_to_char(char *str)
{
	int	i;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (ft_strdup(str));
	return (ft_substr(str, 0, i));
}

t_list	*ft_lst_new(char *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->string = ft_strdup(content);
	new->var = str_to_char(content);
	new->var_content = str_from_char(content);
	new->next = NULL;
	return (new);
}
