/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:13:07 by cassie            #+#    #+#             */
/*   Updated: 2024/03/18 14:10:59 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_here_doc(char *limiter)
{
	char	*buf;
	size_t	size;

	buf = readline("> ");
	if (buf == NULL)
		return ((void)write(2, "minishell: warning: here-document delimited\
				by end-of-file (wanted `stop')\n", 75));
	size = ft_strlen(limiter) + 1;
	while (ft_strncmp(buf, limiter, size))
	{
		free(buf);
		buf = readline("> ");
		if (buf == NULL)
			return ((void)write(2, "minishell: warning: here-document delimited\
				by end-of-file (wanted `stop')\n", 75));
	}
	free(buf);
}

static size_t	check_hd(char *in, size_t i, size_t j, size_t count)
{
	char	*limiter;

	while (in[i] == ' ')
		i++;
	if (in[i] == '>' || in[i] == '<' || in[i] == '|')
		return (ft_strlen(in));
	while (in[i] != ' ' && in[i] != '>' && in[i] != '<' && in[i] != '|')
	{
		count++;
		i++;
	}
	limiter = malloc(sizeof (char) * count + 1);
	if (!limiter)
		return (ft_strlen(in));
	i -= count;
	while (in[i] != ' ' && in[i] != '>' && in[i] != '<' && in[i] != '|')
		limiter[j++] = in[i++];
	limiter[j] = '\0';
	if (limiter && limiter[0])
	{
		do_here_doc(limiter);
		free(limiter);
	}
	return (i);
}

void	check_here_doc(char *in, size_t i)
{
	while (in && in[++i])
	{
		if (in[i] == '>')
		{
			i++;
			if (in[i] == '>')
				i++;
			while (in[i] == ' ')
				i++;
			if (in[i] == '>' || in[i] == '<' || in[i] == '|' || in[i] == '\0')
				return ;
		}
		else if (in[i] == '<' && in[i + 1] != '<')
		{
			i++;
			while (in[i] == ' ')
				i++;
			if (in[i] == '>' || in[i] == '<' || in[i] == '|' || in[i] == '\0')
				return ;
		}
		else if (in[i] == '<' && in[i + 1] == '<')
			i = check_hd(in, i + 2, 0, 0);
	}
}
