/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:48:43 by cassie            #+#    #+#             */
/*   Updated: 2024/03/11 17:09:06 by cassie           ###   ########.fr       */
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

int	ft_cd(char **cmd, t_list **env, t_error *err)
{
	t_list *temp;
	t_list *temp_current_pwd;
	t_list *temp_old_pwd;
	char	*current_pwd;

	temp_current_pwd = check_cmd_env("PWD", env);
	temp_old_pwd = check_cmd_env("OLDPWD", env);
	current_pwd = ft_strdup(temp_current_pwd->var_content); 
	if (tab_size(cmd) > 2)
	{
		err->code = 1;
		ft_putstr_fd("cd : too many arguments\n", 2);
	}
	if (tab_size(cmd) == 1)
	{
		temp = check_cmd_env("HOME", env);
		if (!temp || chdir(temp->var_content) != 0)
			perror("cd");
		else
		{
			free(temp_current_pwd->var_content);
			temp_current_pwd->var_content = ft_strdup(temp->var_content);
		}
	}
	if (tab_size(cmd) == 2)
	{
		if (chdir(cmd[1]) != 0)
		{
			perror("cd :");
			err->code = 1;
		}
		else
		{
			free(temp_current_pwd->var_content);
			temp_current_pwd->var_content = ft_strdup(cmd[1]);
		}
	}
	if (temp_old_pwd->var_content) 
		free(temp_old_pwd->var_content);
	temp_old_pwd->var_content = ft_strdup(current_pwd);
	return (0);
}
