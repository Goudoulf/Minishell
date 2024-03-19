/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq < rjacq@student.42lyon.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:06:13 by rjacq             #+#    #+#             */
/*   Updated: 2024/03/19 13:28:20 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_here_doc(char *limit, int pipefd[2], t_list **env, t_error *err)
{
	char	*buf;
	size_t	size;

	buf = readline("> ");
	if (buf == NULL)
	{
		write(2, "minishell: warning: here-document delimited by ", 47);
		write(2, "end-of-file (wanted `stop')\n", 28);
		return ;
	}
	size = ft_strlen(limit) + 1;
	while (ft_strncmp(buf, limit, size))
	{
		buf = check_dollars(buf, env, err);
		ft_printf(pipefd[1], "%s\n", buf);
		free(buf);
		buf = readline("> ");
		if (buf == NULL)
		{
			write(2, "minishell: warning: here-document delimited by ", 47);
			write(2, "end-of-file (wanted `stop')\n", 28);
			return ;
		}
	}
	free(buf);
}

int	for_each_here_doc(t_cmd *cmd, t_list **env, t_error *err)
{
	size_t	i;
	bool	first;

	while (cmd)
	{
		first = true;
		i = -1;
		while (cmd->here_doc && cmd->here_doc[++i])
		{
			if (first == false)
				closepipe(cmd->pipe_dchevron);
			first = false;
			if (pipe(cmd->pipe_dchevron))
				return (-1);
			do_here_doc(&cmd->here_doc[i][2], cmd->pipe_dchevron, env, err);
		}
		cmd = cmd->next;
	}
	return (0);
}
