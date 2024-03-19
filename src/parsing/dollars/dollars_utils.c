/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:03:27 by cassie            #+#    #+#             */
/*   Updated: 2024/03/19 15:15:35 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_quote(bool *quote, char *c_quote, char char_line)
{
	if (*quote == false)
	{
		*quote = true;
		*c_quote = char_line;
	}
	else
	{
		*quote = false;
		*c_quote = 0;
	}
}

char	*env_replace2(char *temp, t_list *env_m, t_error *err)
{
	if (!env_m && !ft_strncmp("?", temp, 2))
	{
		free(temp);
		temp = ft_itoa(err->code);
		return (temp);
	}
	else if (!env_m)
	{
		free(temp);
		temp = ft_strdup("\0");
		return (temp);
	}
	else
	{
		free(temp);
		temp = ft_strdup(env_m->var_content);
		return (temp);
	}
}

int	not_in_quote(char *s, int j)
{
	char	c_quote;
	bool	quote;
	int		i;

	i = 0;
	c_quote = 0;
	quote = false;
	while (s[i])
	{
		if (quote == false && (s[i] == '\"' || s[i] == '\''))
			set_quote(&quote, &c_quote, s[i]);
		else if (quote == true && s[i] == c_quote)
			set_quote(&quote, &c_quote, s[i]);
		if (i == j && quote == false)
			return (1);
		i++;
	}
	return (0);
}
