/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 11:58:58 by cassie            #+#    #+#             */
/*   Updated: 2024/03/11 09:43:20 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_quote(bool *quote, char *c_quote, char char_line)
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

static int count_dollar(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '$')
			count++;
		i++;
	}
	return (count);
}

int	start_dollar(char *line, int dollar_num)
{
	int	i;
	int	j;
	char	c_quote;
	bool	quote;
	
	i = 0;
	j = 0;
	c_quote = 0;
	quote = false;
	while (line[i])
	{
		if (quote == false && (line[i] == '\"' || line[i] == '\''))
			set_quote(&quote, &c_quote, line[i]);
		else if (quote == true && line[i] == c_quote)
			set_quote(&quote, &c_quote, line[i]);
		if (c_quote != '\'' && line[i] == '$' && j == dollar_num)
			return (i);
		else if (c_quote != '\'' && line[i] == '$')
			j++;
		i++;
	}
	return (-1);
}

char	*check_dollars(char *line, t_list **env, t_error *err)
{
	int	i;
	int	j;
	int	old_count;
	int	new_count;

	i = start_dollar(line, 0);
	j = 0;
	old_count = count_dollar(line);
	if (i < 0)
		return (line);
	while(i >= 0)
	{
		line = replace_dollar(line, env, j, err);
		new_count = count_dollar(line);
		if ( new_count == old_count)
			j++;
		else
			old_count = new_count;
		i = start_dollar(line, j);
	}
	return (line);
}
