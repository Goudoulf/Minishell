/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 11:58:58 by cassie            #+#    #+#             */
/*   Updated: 2024/03/08 17:10:26 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_end(int c)
{
	if (c == ' ' || c == '\t' || c == '\'' || c == '\"' || c == '|' || c == '\0' || c == '$')
		return (1);
	else
		return (0);
}

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

static void	free_temp(char *s2, char *s3, char *s4)
{
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
}

static char *env_replace(char *temp, t_list *env_m, t_error *err)
{
	if (!env_m && !ft_strncmp("?", temp, ft_strlen(temp)))
	{
		free(temp);
		temp = ft_itoa(err->code);
		return (temp);
	}
	else if (!env_m)
	{
		free(temp);
		temp = ft_strdup("\0");
		return (temp);
	}
	else
	{
		free(temp);
		temp = ft_strdup(env_m->var_content);
		return (temp);
	}
}

static char *replace_dollar(char *line, t_list **env, int start, t_error *err)
{
	t_list *env_match;
	char *temp1;
	char *temp2;
	char *temp3;
	int	end;

	start = start_dollar(line, start);
	if (ft_is_end(line[start + 1]))
		return (line);
	end = end_dollar(line, start);
	temp1 = ft_substr(line, 0, start);
	temp2 = ft_substr(line, start + 1 + end, ft_strlen(line));
	temp3 = ft_substr(line, start + 1, end);
	env_match = check_cmd_env(temp3, env);
	temp3 = env_replace(temp3, env_match, err);
	free(line);
	line = ft_strjoin(temp1, temp3);
	free(temp1);
	temp1 = ft_strjoin(line, temp2);
	free_temp(temp2, temp3, line);
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
		line = replace_dollar(line, env, j, err);
		new_count = count_dollar(line);
		if ( new_count == old_count)
			j++;
		else
			old_count = new_count;
		i = start_dollar(line, j);
	}
	return (line);
}
