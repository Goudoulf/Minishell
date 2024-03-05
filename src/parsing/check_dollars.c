/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 11:58:58 by cassie            #+#    #+#             */
/*   Updated: 2024/03/05 12:55:31 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static char	ft_strcpy8(char *destination, const char *source)
{
	int	i;

	i = 0;
	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
	return (*destination);
}

static char	*ft_strjoin_free(const char *s1, const char *s2)
{
	char	*temp;

	temp = NULL;
	if ((s1) && (s2))
	{
		temp = malloc((ft_strlen(s1)) + (ft_strlen(s2) + 1));
		if (!temp)
			return (NULL);
		ft_strcpy8(temp, s1);
		ft_strcpy8(&temp[ft_strlen(s1)], s2);
	}
	return (temp);
}*/
static int	ft_is_end(int c)
{
	if (c == ' ' || c == '\t' || c == '\'' || c == '\"' || c == '|' || c == '\0' || c == '$')
		return (1);
	else
		return (0);
}

/*static int	ft_is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}*/

static t_list	*check_cmd_env(char *arg, t_list **env)
{
	t_list	*temp;

	temp = *env;
	while (temp)
	{
		if (!ft_strncmp(temp->var, arg, ft_strlen(arg)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static void	set_quote(bool *quote, char *c_quote, char char_line)
{
	if (*quote == false)
	{
		*quote = true;
		*c_quote = char_line;
	}
	else
	{
		*quote = false;
		*c_quote = 0;
	}
}

static int	end_dollar(char *line, int start)
{
	int	end;

	end = 0;
	start++;
	while (line[start] && !ft_is_end(line[start]))
	{
		start++;
		end++;
	}
	return (end);
}

static int	start_dollar(char *line, int dollar_num)
{
	int	i;
	int	j;
	char	c_quote;
	bool	quote;
	
	i = 0;
	j = 0;
	c_quote = 0;
	quote = false;
	while (line[i])
	{
		if (quote == false && (line[i] == '\"' || line[i] == '\''))
			set_quote(&quote, &c_quote, line[i]);
		else if (quote == true && line[i] == c_quote)
			set_quote(&quote, &c_quote, line[i]);
		if (c_quote != '\'' && line[i] == '$' && j == dollar_num)
			return (i);
		else if (c_quote != '\'' && line[i] == '$')
			j++;
		i++;
	}
	return (-1);
}

static char *replace_dollar(char *line, t_list **env, int start, int end, t_error *err)
{
	t_list *env_match;
	char *temp1;
	char *temp2;
	char *temp3;
	char *final;

	start = start_dollar(line, start);
	if (ft_is_end(line[start + 1]))
		return (line);
	end = end_dollar(line, start);
	temp1 = ft_substr(line, 0, start);
//	printf("temp1 =%s\n", temp1);
	temp2 = ft_substr(line, start + 1 + end, ft_strlen(line));
//	printf("temp2 =%s\n", temp2);
	temp3 = ft_substr(line, start + 1, end);
//	printf("temp3 =%s\n", temp3);
	env_match = check_cmd_env(temp3, env);
	free(temp3);
	if (!env_match && !ft_strncmp("?", temp3, ft_strlen(temp3)))
		temp3 = ft_itoa(err->code);
	else if (!env_match)
		temp3 = ft_strdup("\0");
	else
		temp3 = ft_strdup(env_match->var_content);
	final = ft_strjoin(temp1, temp3);
	free(temp1);
	free(temp3);
	temp1 = ft_strjoin(final, temp2);
	free(temp2);
	free(final);
	free(line);
	return (temp1);
}

static int count_dollar(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*check_dollars(char *line, t_list **env, t_error *err)
{
	int	i;
	int	j;
	int	old_count;
	int	new_count;

	i = start_dollar(line, 0);
	j = 0;
	old_count = count_dollar(line);
	if (i < 0)
		return (line);
	while(i >= 0)
	{
		line = replace_dollar(line, env, j, 0, err);
		new_count = count_dollar(line);
		if ( new_count == old_count)
			j++;
		else
			old_count = new_count;
		i = start_dollar(line, j);
	}
	return (line);
}
