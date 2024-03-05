/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:17:32 by cassie            #+#    #+#             */
/*   Updated: 2024/03/05 14:26:36 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t new_size(char *str)
{
	size_t	i;
	size_t	count;
	bool quote;
	char	c_quote;

	quote = false;
	c_quote = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quote)
		{
			quote = true;
			c_quote = str[i];
			i++;
		}
		else if (str[i] == c_quote && quote == true)
		{
			quote = false;
			c_quote = 0;
			i++;
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

static char *delete_quote(char *cmd_arg)
{
	char *temp;
	size_t	i;
	size_t	j;
	size_t size;
	char	c_quote;
	
	i = 0;
	j = 0;
	c_quote = 0;
	size = new_size(cmd_arg);
	printf("oldsize %zu\n", ft_strlen(cmd_arg));
	printf("newsize %zu\n", size);
	temp = malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	while (j < size)
	{
		if ((cmd_arg[i] == '\'' || cmd_arg[i] == '\"') && !c_quote)
		{
			c_quote = cmd_arg[i];
			i++;
		}
		else if (cmd_arg[i] == c_quote && c_quote)
		{
			c_quote = 0;
			i++;
		}
		else
		{
			temp[j] = cmd_arg[i];
			j++;
			i++;
		}
	}
	temp[j] = '\0';
	free(cmd_arg);
	return (temp);
}

void clean_quote(t_cmd **cmd)
{
	t_cmd	*temp;
	int	i;

	temp = *cmd;
	if (!temp)
		return ;
	while (temp)
	{
		i = 0;
		while (temp->cmd[i])
		{
			temp->cmd[i] = delete_quote(temp->cmd[i]);
			i++;
		}
		temp = temp->next;
	}
}
