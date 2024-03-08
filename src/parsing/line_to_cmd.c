/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:31:34 by cassie            #+#    #+#             */
/*   Updated: 2024/03/07 11:00:35 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_tab(size_t nelem)
{
	size_t	i;
	char **tab;

	i = 0;
	tab = NULL;
//	printf("size = %zu\n", nelem);
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

static t_cmd	*ft_cmd_new(char **command, char **redirection, t_list **env)
{
	t_cmd	*new;
	char	*path;

	new = malloc(sizeof(t_cmd));
	path = get_value(env, "PATH");
	if (!new)
		return (NULL);
	new->cmd = command;
	if (command)
		new->path = find_path(command[0], path);
	else
		new->path = NULL;
	new->redirection = redirection;
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

void	line_to_cmd(t_cmd **cmd, char *line, t_list **env)
{
	char	**command;
	char	**redirection;
	char	*token;
	int		i;
	int		k;

	i = 0;
	k = 0;
	redirection = create_tab(infile_count(line) + outfile_count(line));
	command = create_tab(cmd_count(line, ' ') - infile_count(line) - outfile_count(line));
	// special token for export
	token = ft_strtok_quote(line, " ");
	while (token)
	{
		if (!token)
			break;
		else if (token[0] == '<' || token[0] == '>')
			redirection[i++] = ft_strdup(token);
		else if (token)
			command[k++] = ft_strdup(token);
		token = ft_strtok_quote(NULL, " ");
	}
	free(line);
	ft_cmdadd_back(cmd, ft_cmd_new(command, redirection, env));
}