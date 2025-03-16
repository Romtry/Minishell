/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:13:03 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/16 16:23:01 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

volatile sig_atomic_t	g_heredoc_interrupted = 0;

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_done = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\004");
	g_heredoc_interrupted = 1;
}

void	read_heredoc_lines(t_cmd *cmd, int pipe_fd, char *delimiter)
{
	char	*line;

	while (!g_heredoc_interrupted)
	{
		line = readline("heredoc> ");
		if (g_heredoc_interrupted || !line)
		{
			free(line);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd, line, ft_strlen(line));
		write(pipe_fd, "\n", 1);
		free(line);
	}
	(void)cmd;
}

int	handle_heredoc(t_cmd *cmd, char *delimiter)
{
	int					pipe_fd[2];
	void				(*old_sigint)(int);

	if (pipe(pipe_fd) == -1)
		return (perror("minishell: pipe"), -1);
	g_heredoc_interrupted = 0;
	old_sigint = signal(SIGINT, heredoc_sigint_handler);
	read_heredoc_lines(cmd, pipe_fd[1], delimiter);
	signal(SIGINT, old_sigint);
	close(pipe_fd[1]);
	if (g_heredoc_interrupted)
	{
		close(pipe_fd[0]);
		cmd->heredoc_fd = open("/dev/null", O_RDONLY);
		return (1);
	}
	else
		cmd->heredoc_fd = pipe_fd[0];
	return (0);
}

int	handle_heredoc_redir(t_cmd *cmd, int *i, int k)
{
	if (handle_heredoc(cmd, cmd->word[k][*i + 1]) == -1)
		return (-1);
	if (g_heredoc_interrupted)
	{
		g_heredoc_interrupted = 0;
		*i += 2;
		return (-1);
	}
	*i += 2;
	return (0);
}
