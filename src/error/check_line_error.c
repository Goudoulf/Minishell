/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq < rjacq@student.42lyon.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:28:16 by cassie            #+#    #+#             */
/*   Updated: 2024/03/15 11:47:58 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_chevron_max(char *line)
{
	int	i;
	int	count;
	char	c_quote;

	i = 0;
	c_quote = 0;
	while (line[i])
	{
		count = 0;
		if ((line[i] == '\'' || line[i] == '\"') && !c_quote)
			c_quote = line[i];
		else if (line[i] == c_quote)
			c_quote = 0;
		while (ft_is_chevron(line[i]) && !c_quote)
		{
			i++;
			count++;
			if (count > 2)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				write(2, &line[i], 1);
				ft_putstr_fd("\'\n", 2);
				return (0);
			}
		}
		if (line[i])
			i++;
	}
	return (1);
}

static int	check_double_chevron(char *line)
{
	int	i;
	char	c_quote;

	i = 0;
	c_quote = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && !c_quote)
			c_quote = line[i];
		else if (line[i] == c_quote)
			c_quote = 0;
		if (ft_is_chevron(line[i]) && ft_is_chevron(line[i + 1]) && !c_quote)
		{
			if (line[i] != line[i + 1])
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				write(2, &line[i + 1], 1);
				ft_putstr_fd("\'\n", 2);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

static int	check_chevron_content(char *line)
{
	char	c_quote;
	int	i;

	i = 0;
	c_quote = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && !c_quote)
			c_quote = line[i];
		else if (line[i] == c_quote)
			c_quote = 0;
		if (ft_is_chevron(line[i]) && !ft_is_chevron(line[i + 1]) && !c_quote)
		{
			i++;
			while (ft_is_space(line[i]))
				i++;
			if (ft_is_chevron(line[i]) || line[i] == '|' || line[i] == '\0')
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				if (line[i] == '\0')
					write(2, "newline", 7);
				else
					write(2, &line[i], 1);
				ft_putstr_fd("\'\n", 2);
				return (0);
			}
		}
		else
			i++;
	}
	return (1);
}

static int	check_pipe(char *line)
{
	int	i;
	char	c_quote;

	c_quote = 0;
	i = 0;
	while (ft_is_space(line[i]))
		i++;
	if (line[i] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		write(2, &line[i], 1);
		ft_putstr_fd("\'\n", 2);
		return (0);
	}
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && !c_quote)
			c_quote = line[i];
		else if (line[i] == c_quote)
			c_quote = 0;
		if (line[i] == '|' && line[i + 1] == '|' && !c_quote)
			return (0);
		if (line[i] == '|' && line[i + 1] != '|' && !c_quote)
		{
			i++;
			while (ft_is_space(line[i]))
				i++;
			if (line[i] == '|' || line[i] == '\0')
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				write(2, &line[i], 1);
				ft_putstr_fd("\'\n", 2);
				return (0);
			}
		}
		else
			i++;
	}
	return (1);
}

int	check_line_error(char *line, t_error *err)
{
	if (!check_chevron_max(line))
	{
		err->code = 2;
		return (0);
	}
	if (!check_double_chevron(line))
	{
		err->code = 2;
		return (0);
	}
	if (!check_chevron_content(line))
	{
		err->code = 2;
		return (0);
	}
	if (!check_pipe(line))
	{
		err->code = 2;
		return (0);
	}
	return (1);
}
