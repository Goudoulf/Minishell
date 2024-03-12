/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 08:31:17 by cassie            #+#    #+#             */
/*   Updated: 2024/03/12 13:17:20 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_strlen_equal(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

static char	*str_from_char(char *str)
{
	int	i;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (ft_strdup("\0"));
	if (str[i] == '=' && !str[i + 1])
		return (ft_strdup("\0"));
	return(ft_substr(str, i + 1, ft_strlen(str)));
}

static char	*str_to_char(char *str)
{
	int	i;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (ft_strdup(str));
	return (ft_substr(str, 0, i));
}

/*static size_t env_size(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}*/

static void	env_print(t_list **env)
{
	t_list *temp;

	temp = get_next_min(env);
	while (temp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(temp->var, 1);
		if (temp->var_content)
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(temp->var_content, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		temp = get_next_min(env);
	}
	ft_lst_set_isprint(env);
}

static void	env_update(t_list *env, char *content)
{
	if (env->var)
		free(env->var);
	env->var = str_to_char(content);
	if (env->var_content)
		free(env->var_content);
	env->var_content = str_from_char(content);
}

static t_list	*check_cmd_env_equal(char *arg, t_list **env)
{
	t_list	*temp;

	temp = *env;
	while (temp)
	{
		if (!ft_strncmp(temp->var, arg, ft_strlen_equal(arg)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static int	cmd_is_valid(char *cmd)
{
	int i;

	i = 0;
	if (cmd && (ft_isdigit(cmd[i]) || cmd[i] == '='))
	{
		ft_putstr_fd("minishell: line 0: export: `", 2);
		write(2, &cmd[i], 1);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		return (0);
	}
	while (cmd[i] && cmd[i] != '=')
	{
		if (ft_isalnum(cmd[i]) || cmd[i] == '_' || (cmd[i] == '+' && cmd[i + 1] == '='))
			i++;
		else
		{
			ft_putstr_fd("minishell: line 0: export: `", 2);
			ft_putstr_fd(cmd, 2);
			//write(2, &cmd[i], 1);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			return (0);
		}
	}
	return (1);
}

int	ft_export(t_list **env, char **cmd, t_error *err)
{
	int	i;
	t_list *temp;

	i = 1;
	if (tab_size(cmd) < 2)
	{	
		env_print(env);
		return (0);
	}
	while (cmd[i])
	{
		if (!cmd_is_valid(cmd[i]))
		{
			err->code = 1;
			return (1);
		}
		temp = check_cmd_env_equal(cmd[i], env);
		if (!temp)
			ft_lstadd_back(env, ft_lst_new(cmd[i]));
		else
			env_update(temp, cmd[i]);
		i++;
	}
	return (0);	
}
