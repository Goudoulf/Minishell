/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc_shell_lvl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:07:50 by cassie            #+#    #+#             */
/*   Updated: 2024/03/04 15:36:51 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inc_shell_lvl(t_list **env)
{
	t_list	*temp;
	char *old;
	int	new_int;

	temp = *env;
	if (!env)
		return ;
	while (temp)
	{
		if (!ft_strncmp(temp->var, "SHLVL", ft_strlen(temp->var)))
		{
			old = temp->var_content;
			if (!old)
				return ;
			new_int = ft_atoi(old) + 1;
			free(temp->var_content);
			temp->var_content = ft_itoa(new_int);
			return ;
		}
		temp = temp->next;
	}
}
