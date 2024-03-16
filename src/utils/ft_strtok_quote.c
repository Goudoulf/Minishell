/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_strtok_quote.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: cassie <cassie@student.42lyon.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/02/23 12:42:30 by cassie			   #+#	  #+#			  */
/*	 Updated: 2024/03/15 19:15:30 by cassie			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	is_delim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

static char	*set_ret(char *ret, char **string)
{
	**string = '\0';
	(*string)++;
	return (ret);
}

static char	*get_next_tok(char **string, char *delim, char *c_quote, char *ret)
{
	while (**string != '\0')
	{
		if (**string == '\"' || **string == '\'')
			*c_quote = **string;
		if (is_delim(**string, delim) && !(*c_quote))
		{
			(*string)++;
			continue ;
		}
		ret = *string;
		(*string)++;
		while (**string != '\0')
		{
			if ((**string == '\"' || **string == '\''))
				quote_mode(c_quote, **string);
			if (is_delim(**string, delim) && !(*c_quote))
				return (set_ret(ret, string));
			(*string)++;
		}
	}
	return (ret);
}

char	*ft_strtok_quote(char *string, char *delim)
{
	static char	*string_copy;
	char		c_quote;
	char		*token;

	c_quote = '\0';
	if (!string)
		string = string_copy;
	if (!string)
		return (NULL);
	token = get_next_tok(&string, delim, &c_quote, NULL);
	string_copy = string;
	return (token);
}
