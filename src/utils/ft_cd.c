/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:48:43 by cassie            #+#    #+#             */
/*   Updated: 2024/03/19 15:41:02 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_home(t_list *temp, t_list **env, t_error *err, t_list *cur_p)
{
	temp = check_cmd_env("HOME", env);
	if (!temp || chdir(temp->var_content) != 0)
		stderr_cd("HOME not set", 1, err);
	else
	{
		free(cur_p->var_content);
		cur_p->var_content = ft_strdup(temp->var_content);
		if (!cur_p->var_content)
			quit_error(err);
	}
}

static void	ft_cd_min(t_list *old_pwd, t_error *err, t_list *cur_p)
{
	if (!old_pwd)
		stderr_cd("OLDPWD not set", 1, err);
	else if (chdir(old_pwd->var_content) != 0)
		stderr_cd(strerror(errno), 1, err);
	else
	{
		free(cur_p->var_content);
		ft_putstr_fd(old_pwd->var_content, 1);
		write(1, "\n", 1);
		cur_p->var_content = ft_pwd2(10, 1);
		if (!cur_p->var_content)
			quit_error(err);
	}
}

static void	ft_cd_path(char **cmd, t_list **env, t_error *err, t_list *cur_p)
{
	if (chdir(cmd[1]) != 0)
		stderr_cd(strerror(errno), 1, err);
	else if (!cur_p)
		ft_lstadd_back(env, ft_lst_new(ft_strjoin("PWD=", ft_pwd2(10, 1))));
	else
	{
		free(cur_p->var_content);
		cur_p->var_content = ft_pwd2(10, 1);
		if (!cur_p->var_content)
			quit_error(err);
	}
}

static void	ft_cd_old(t_list *old_pwd, t_list **env, char *cur_p, t_error *err)
{
	if (old_pwd && old_pwd->var_content)
	{
		free(old_pwd->var_content);
		old_pwd->var_content = ft_strdup(cur_p);
		if (!old_pwd->var_content)
		{
			free(cur_p);
			quit_error(err);
		}
	}
	else
		ft_lstadd_back(env, ft_lst_new(ft_strjoin("OLDPWD=", cur_p)));
	free (cur_p);
}

int	ft_cd(char **cmd, t_list **env, t_error *err)
{
	t_list	*temp;
	t_list	*temp_current_pwd;
	t_list	*temp_old_pwd;
	char	*current_pwd;

	temp = NULL;
	temp_current_pwd = check_cmd_env("PWD", env);
	temp_old_pwd = check_cmd_env("OLDPWD", env);
	current_pwd = ft_pwd2(10, 1);
	err->code = 0;
	if (tab_size(cmd) > 2)
		stderr_cd("too many arguments", 1, err);
	else if (tab_size(cmd) == 1 || (tab_size(cmd) == 2
			&& !ft_strncmp(cmd[1], "--", 3)))
		ft_cd_home(temp, env, err, temp_current_pwd);
	else if (tab_size(cmd) == 2 && !ft_strncmp(cmd[1], "-", 2))
		ft_cd_min(temp_old_pwd, err, temp_current_pwd);
	else if (tab_size(cmd) == 2)
		ft_cd_path(cmd, env, err, temp_current_pwd);
	ft_cd_old(temp_old_pwd, env, current_pwd, err);
	return (0);
}
