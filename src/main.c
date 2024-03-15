/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq < rjacq@student.42lyon.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:12:26 by cassie            #+#    #+#             */
/*   Updated: 2024/03/15 15:25:37 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

#define CYELLOW "\001\e[0;31m\002"
#define RESET   "\001\e[0m\002"

static void	quit_eof(t_list **env, t_cmd **cmd, t_error *err)
{
	rl_clear_history();
	ft_lstclear(env);
	ft_cmdclear(cmd);
	//ft_putstr_fd("exit\n", 1);
	exit(err->code);
}

static void	quit_exit(t_list **env, t_cmd **cmd, t_error *err)
{
	rl_clear_history();
	ft_lstclear(env);
	ft_cmdclear(cmd);
	exit(err->code);
}

void	do_here_doc(char *limiter)
{
	char	*buf;
	size_t	size;

	buf = readline("> ");
	if (buf == NULL)
		return ;
	size = ft_strlen(limiter) + 1;
	while (ft_strncmp(buf, limiter, size))
	{
		free(buf);
		buf = readline("> ");
		if (buf == NULL)
			return ;
	}
	free(buf);
}

void	check_here_doc(char *input)
{
	size_t	i;
	size_t	j;
	size_t	count;
	char	*limiter;
	
	i = -1;
	while (input && input[++i])
	{
		if (input[i] == '>')
		{
			i++;
			if (input[i] == '>')
				i++;
			while(input[i] == ' ')
				i++;
			if (input[i] == '>' || input[i] == '<' || input[i] == '|' || input[i] == '\0')
				return;
		}
		else if (input[i] == '<' && input[i + 1] != '<')
		{
			i++;
			while(input[i] == ' ')
				i++;
			if (input[i] == '>' || input[i] == '<' || input[i] == '|' || input[i] == '\0')
				return;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			count = 0;
			i += 2;
			while (input[i] == ' ')
				i++;
			if (input[i] == '>' || input[i] == '<' || input[i] == '|')
				return;
			while (input[i] != ' ' && input[i] != '>' && input[i] != '<' && input[i] != '|')
			{
				count++;
				i++;
			}
			limiter = malloc(sizeof (char) * count + 1);
			if (!limiter)
				return;
			i -= count;
			j = 0;
			while (input[i] != ' ' && input[i] != '>' && input[i] != '<' && input[i] != '|')
				limiter[j++] = input[i++];
			limiter[j] = '\0';
			if (limiter && limiter[0])
			{
				do_here_doc(limiter);
				free(limiter);
			}
		}
	}
}

int main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	t_list	*env;
	t_error	err;
	char	*input;

	env = NULL;
	cmd = NULL;
	init_all(&cmd, &env, &err, envp);
	signal_handling();
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		input = argv[2];
		if (!input)
			quit_eof(&env, &cmd, &err);
		if (input && *input)
		{
			add_history(input);
			if (check_line_error(input, &err))
			{
				line_parsing(&cmd, input, &env, &err);
				err.code = exec_line(cmd, &env, &err);
			//	check_cmd(input, &env, &cmd, &err);
			}
			ft_cmdclear(&cmd);
		}
		exit(err.code);
	}
	while(1)
	{
		if (isatty(fileno(stdin)))
			input = readline(CYELLOW "[Minishell]: " RESET);
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			input = ft_strtrim(line, "\n");
			free(line);
		}
		//input = readline(CYELLOW "[Minishell]: " RESET);
		if (!input)
			quit_eof(&env, &cmd, &err);
		if (input && *input)
		{
			add_history(input);
			if (check_line_error(input, &err))
			{
				line_parsing(&cmd, input, &env, &err);
				err.code = exec_line(cmd, &env, &err);
			//	check_cmd(input, &env, &cmd, &err);
			}
			else
				check_here_doc(input);
			ft_cmdclear(&cmd);
		}
		free(input);
		if (err.do_exit == true)
			quit_exit(&env, &cmd, &err);
	}
}
