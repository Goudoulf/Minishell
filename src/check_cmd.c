/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq < rjacq@student.42lyon.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:06:40 by cassie            #+#    #+#             */
/*   Updated: 2024/03/13 13:33:50 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(char *input, t_list **env, t_cmd **command, t_error *err)
{
	t_cmd *temp;
	char **com;

	com = NULL;
	temp = *command;
	if (temp)
		com = temp->cmd;
	if (com && !ft_strncmp(com[0], "export", 7))
		ft_export(env, com, err);
	if (com && !ft_strncmp(com[0], "unset", 7))
		ft_unset(env, com, err);
	if (com && !ft_strncmp(com[0], "exit", 5))
		ft_exit(com, err);
	if (com && !ft_strncmp(com[0], "echo", 5))
		ft_echo(com, err);
	if (com && !ft_strncmp(com[0], "cd", 5))
		ft_cd(com, env, err);
	if (com && !ft_strncmp(input, "pwd", 4))
		ft_pwd(com, err);
	if (!ft_strncmp(input, "env", 5))
		ft_lst_print(env, err);
	if (err->do_exit == true)
	{	
		free(input);
		rl_clear_history();
		ft_cmdclear(command);
		ft_lstclear(env);
		ft_putstr_fd("exit\n", 1);
		exit(err->code);
	}
}
