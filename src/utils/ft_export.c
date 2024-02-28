/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 08:31:17 by cassie            #+#    #+#             */
/*   Updated: 2024/02/28 20:34:56 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t env_size(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static void	env_print(t_list **env, int fd)
{
	t_list *temp;

	temp = *env;
// ajouter tri en ascii
	while (temp)
	{
		ft_putstr_fd(temp->var, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd(temp->var_content, 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd("\n", 1);
		temp = temp->next;
	}
}

/*static int	ft_strcmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (i < n)
		return (str1[i] - str2[i]);
	return (0);
}*/
static void	env_update(t_list *env, char *content)
{
	env->string = ft_strdup(content);
	env->var = str_to_char(content);
	env->var_content = str_from_char(content);
}
static t_list	*check_cmd_env(char *arg, t_list **env)
{
	t_list	*temp;

	temp = *env;
	while (temp)
	{
		if (!ft_strcmp(temp->var, arg, ft_strlen(arg)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static char	**env_add(t_data **data, char *arg)
{
	size_t	size;

	size = env_size(data->env);
}

int	ft_export(t_list **env, char **cmd, int	fd)
{
	int	i;
	t_list temp;

	i = 1;
	temp = NULL;
	if (tab_size(cmd) < 2)
		return (envp_print(env, fd), 0);
	while (cmd[i])
	{
		temp = check_cmd_env(cmd[i], env);
		if (!temp)
			ft_lstadd_back(env, ft_lst_new(cmd[i]));
		else
			env_update(temp, cmd[i]);
		i++;
	}
	return (0);
}
