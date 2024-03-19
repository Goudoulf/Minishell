/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:13:07 by cassie            #+#    #+#             */
/*   Updated: 2024/03/19 17:04:44 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_here_doc(char *limiter)
{
	char	*buf;
	size_t	size;

	buf = readline("> ");
	if (buf == NULL)
	{
		ft_putstr_fd("minishell: warning: here-document delimited", 2);
		ft_putstr_fd("by end-of-file (wanted `stop')\n", 2);
		return ;
	}
	size = ft_strlen(limiter) + 1;
	while (ft_strncmp(buf, limiter, size))
	{
		free(buf);
		buf = readline("> ");
		if (buf == NULL)
		{
			ft_putstr_fd("minishell: warning: here-document delimited", 2);
			ft_putstr_fd("by end-of-file (wanted `stop')\n", 2);
			return ;
		}
	}
	free(buf);
}

static size_t	check_hd(char *p, size_t i, size_t j, size_t count)
{
	char	*limiter;

	while (p[i] == ' ')
		i++;
	if (p[i] == '>' || p[i] == '<' || p[i] == '|')
		return (ft_strlen(p));
	while (p[i] && p[i] != ' ' && p[i] != '>' && p[i] != '<' && p[i] != '|')
	{
		count++;
		i++;
	}
	limiter = malloc(sizeof (char) * count + 1);
	if (!limiter)
		return (ft_strlen(p));
	i -= count;
	while (p[i] && p[i] != ' ' && p[i] != '>' && p[i] != '<' && p[i] != '|')
		limiter[j++] = p[i++];
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
	while (in && i < ft_strlen(in))
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
