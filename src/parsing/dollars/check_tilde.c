/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tilde.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:13:06 by cassie            #+#    #+#             */
/*   Updated: 2024/03/19 12:25:53 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tilde(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (line[i] == '~' && line[i + 1] == '\0')
		return (1);
	while (line[i])
	{
		if (line[i] == '~' && (line[i + 1] == ' ' || line[i + 1] == '/'
				|| line[i + 1] == '\0') && ((i > 0 && (line[i - 1] == ' '
						|| line[i - 1] == '/'))))
			count++;
		i++;
	}
	return (count);
}

int	start_tilde(char *line, int tilde_num)
{
	int		i;
	int		j;
	char	c_quote;
	bool	quote;

	i = 0;
	j = 0;
	c_quote = 0;
	quote = false;
	while (line && line[i])
	{
		if (quote == false && (line[i] == '\"' || line[i] == '\''))
			set_quote(&quote, &c_quote, line[i]);
		else if (quote == true && line[i] == c_quote)
			set_quote(&quote, &c_quote, line[i]);
		if (c_quote == '\0' && line[i] == '~' && j == tilde_num)
			return (i);
		else if (c_quote == '\0' && line[i] == '~')
			j++;
		i++;
	}
	return (-1);
}

char	*check_tilde(char *line, t_list **env, t_error *err)
{
	int		i;
	int		j;
	int		old_count;
	int		new_count;

	i = start_tilde(line, 0);
	j = 0;
	old_count = count_tilde(line);
	if (old_count == 0)
		return (line);
	while (i >= 0)
	{
		line = replace_tilde(line, env, j);
		if (!line)
			quit_error(err);
		new_count = count_tilde(line);
		if (new_count == old_count)
			j++;
		else
			old_count = new_count;
		i = start_tilde(line, j);
	}
	return (line);
}
