/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:31:34 by cassie            #+#    #+#             */
/*   Updated: 2024/02/25 19:16:15 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_tab(size_t nelem)
{
	size_t	i;
	char **tab;

	i = 0;
	tab = NULL;
	if (nelem == 0)
		return (NULL);
	tab = malloc(sizeof(char *) * (nelem + 1));
	if (!tab)
		return (NULL);
	while (i < nelem)
	{
		tab[i] = NULL;
		i++;
	}
	tab[i] = 0; 
	return (tab);
}

static t_cmd	*ft_cmd_new(char **command, char **input, char **output)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = command;
	new->path = NULL;
	new->input_file = input;
	new->output_file = output;
	new->next = NULL;
	return (new);
}

static void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*temp;

	temp = *cmd;
	if (new == NULL)
		return ;
	if (*cmd == NULL)
	{
		*cmd = new;
		new->next = NULL;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	line_to_cmd(t_cmd **cmd, char *line)
{
	char	**command;
	char	**input;
	char	**output;
	char	*token;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	input = create_tab(infile_count(line));
	output = create_tab(outfile_count(line));
	command = create_tab(cmd_count(line, ' ') - infile_count(line) - outfile_count(line));
	token = ft_strtok_quote(line, " ");
	while (token)
	{
		if (!token)
			break;
		else if (token[0] == '<')
			input[i++] = ft_strdup(token);
		else if (token[0] == '>')
			output[j++] = ft_strdup(token);
		else if (token)
			command[k++] = ft_strdup(token);
		token = ft_strtok_quote(NULL, " ");
	}
	ft_cmdadd_back(cmd, ft_cmd_new(command, input, output));
}
