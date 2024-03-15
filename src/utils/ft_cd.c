/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:48:43 by cassie            #+#    #+#             */
/*   Updated: 2024/03/15 11:04:25 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static t_list	*check_cmd_env(char *arg, t_list **env)
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
}*/
static char	*ft_pwd2(void)
{
	char	*str;
	char	*temp;
	int		size;
	int		i;

	str = NULL;
	size = 10;
	i = 1;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (i * 10  < 4096)
	{
		temp = getcwd(str, size * i);
		if (!temp)
		{
			free(str);
			i++;
			str = malloc(sizeof(char) * size * i + 1);
			if (!str)
				return (NULL);
			str[size * i] = '\0';
		}
		else 
			return (temp);
	}
	return (0);
}

int	ft_cd(char **cmd, t_list **env, t_error *err)
{
	t_list *temp;
	t_list *temp_current_pwd;
	t_list *temp_old_pwd;
	char	*current_pwd;

	temp_current_pwd = check_cmd_env("PWD", env);
	temp_old_pwd = check_cmd_env("OLDPWD", env);
	current_pwd = ft_pwd2();
	err->code = 0;
	if (tab_size(cmd) > 2)
	{
		err->code = 1;
		ft_putstr_fd("cd : too many arguments\n", 2);
	}
	else if (tab_size(cmd) == 1 || (tab_size(cmd) == 2 && !ft_strncmp(cmd[1], "--", 3)))
	{
		temp = check_cmd_env("HOME", env);
		if (!temp || chdir(temp->var_content) != 0)
		{
			ft_putstr_fd("bash: cd: HOME not set\n", 2);
			err->code = 1;
		}
		else
		{
			free(temp_current_pwd->var_content);
			temp_current_pwd->var_content = ft_strdup(temp->var_content);
		}
	}
	else if (tab_size(cmd) == 2 && !ft_strncmp(cmd[1], "-", 2))
	{
		if (!temp_old_pwd)
		{
			ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
			err->code = 1;
		}
		else if (chdir(temp_old_pwd->var_content) != 0)
		{
			perror("cd :");
			err->code = 1;
		}
		else
		{
			free(temp_current_pwd->var_content);
			ft_putstr_fd(temp_old_pwd->var_content, 1);
			write(1, "\n", 1);
			temp_current_pwd->var_content = ft_pwd2();
		}

	}
	else if (tab_size(cmd) == 2)
	{
		if (chdir(cmd[1]) != 0)
		{
			perror("cd :");
			err->code = 1;
		}
		else if (!temp_current_pwd)
		{
			ft_lstadd_back(env, ft_lst_new(ft_strjoin("PWD=", ft_pwd2())));
		}
		else
		{
			free(temp_current_pwd->var_content);
			temp_current_pwd->var_content = ft_pwd2();
		}
	}
	if (temp_old_pwd && temp_old_pwd->var_content)
	{
		free(temp_old_pwd->var_content);
		temp_old_pwd->var_content = ft_strdup(current_pwd);
	}
	else
		ft_lstadd_back(env, ft_lst_new(ft_strjoin("OLDPWD=", current_pwd)));
	free (current_pwd);
	return (0);
}
