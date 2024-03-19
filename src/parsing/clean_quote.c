/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:17:32 by cassie            #+#    #+#             */
/*   Updated: 2024/03/19 15:56:09 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	new_size(char *str, size_t i)
{
	size_t	count;
	char	c_quote;

	c_quote = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !c_quote)
			c_quote = str[i];
		else if (str[i] == c_quote)
			c_quote = 0;
		else
			count++;
		i++;
	}
	return (count);
}

static char	*delete_quote(char *cmd_arg, size_t j, char c_quote, t_error *err)
{
	char	*temp;
	size_t	size;
	size_t	i;

	i = 0;
	size = new_size(cmd_arg, 0);
	temp = malloc(sizeof(char) * (size + 1));
	if (!temp)
		quit_error(err);
	while (j < size)
	{
		if ((cmd_arg[i] == '\'' || cmd_arg[i] == '\"') && !c_quote)
			c_quote = cmd_arg[i++];
		else if (cmd_arg[i] == c_quote)
		{
			c_quote = 0;
			i++;
		}
		else
			temp[j++] = cmd_arg[i++];
	}
	temp[j] = '\0';
	free(cmd_arg);
	return (temp);
}

void	clean_quote(t_cmd **cmd, t_error *err)
{
	t_cmd	*temp;
	int		i;

	temp = *cmd;
	if (!temp)
		return ;
	while (temp)
	{
		i = -1;
		while (temp->cmd && temp->cmd[++i])
			temp->cmd[i] = delete_quote(temp->cmd[i], 0, 0, err);
		i = -1;
		while (temp->redirection && temp->redirection[++i])
			temp->redirection[i] = delete_quote(temp->redirection[i], \
				0, 0, err);
		i = -1;
		while (temp->here_doc && temp->here_doc[++i])
			temp->here_doc[i] = delete_quote(temp->here_doc[i], 0, 0, err);
		temp = temp->next;
	}
}
