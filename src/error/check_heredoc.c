/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:13:07 by cassie            #+#    #+#             */
/*   Updated: 2024/03/16 10:16:11 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_here_doc(char *limiter)
{
	char	*buf;
	size_t	size;

	buf = readline("> ");
	if (buf == NULL)
		return ((void)write(2, "minishell: warning: here-document delimited by end-of-file (wanted `stop')\n", 75));
	size = ft_strlen(limiter) + 1;
	while (ft_strncmp(buf, limiter, size))
	{
		free(buf);
		buf = readline("> ");
		if (buf == NULL)
			return ((void)write(2, "minishell: warning: here-document delimited by end-of-file (wanted `stop')\n", 75));
	}
	free(buf);
}

void	check_here_doc(char *input)
{
	size_t	i;
	size_t	j;
	size_t	count;
	char	*limiter;
	
	i = -1;
	while (input && input[++i])
	{
		if (input[i] == '>')
		{
			i++;
			if (input[i] == '>')
				i++;
			while(input[i] == ' ')
				i++;
			if (input[i] == '>' || input[i] == '<' || input[i] == '|' || input[i] == '\0')
				return;
		}
		else if (input[i] == '<' && input[i + 1] != '<')
		{
			i++;
			while(input[i] == ' ')
				i++;
			if (input[i] == '>' || input[i] == '<' || input[i] == '|' || input[i] == '\0')
				return;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			count = 0;
			i += 2;
			while (input[i] == ' ')
				i++;
			if (input[i] == '>' || input[i] == '<' || input[i] == '|')
				return;
			while (input[i] != ' ' && input[i] != '>' && input[i] != '<' && input[i] != '|')
			{
				count++;
				i++;
			}
			limiter = malloc(sizeof (char) * count + 1);
			if (!limiter)
				return;
			i -= count;
			j = 0;
			while (input[i] != ' ' && input[i] != '>' && input[i] != '<' && input[i] != '|')
				limiter[j++] = input[i++];
			limiter[j] = '\0';
			if (limiter && limiter[0])
			{
				do_here_doc(limiter);
				free(limiter);
			}
		}
	}
}
