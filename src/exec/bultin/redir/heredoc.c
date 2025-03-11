/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:13:03 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/11 14:04:05 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_done = 1;
	close(STDIN_FILENO);
}

int	handle_fd_dup(int fd, int std_fd)
{
	if (dup2(fd, std_fd) == -1)
	{
		perror("minishell: dup2");
		return (-1);
	}
	return (0);
}

void	read_heredoc_lines(t_cmd *cmd, int pipe_fd, char *delimiter)
{
	char	*line;

	while (!cmd->heredoc_interrupted)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			cmd->heredoc_interrupted = 1;
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
}

int	handle_heredoc(t_cmd *cmd, char *delimiter)
{
	int					pipe_fd[2];
	struct sigaction	sa_new;
	struct sigaction	sa_old;

	if (pipe(pipe_fd) == -1)
		return (perror("minishell: pipe"), -1);
	cmd->heredoc_interrupted = 0;
	sa_new.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, &sa_old);
	read_heredoc_lines(cmd, pipe_fd[1], delimiter);
	sigaction(SIGINT, &sa_old, NULL);
	close(pipe_fd[1]);
	cmd->heredoc_fd = pipe_fd[0];
	if (cmd->heredoc_interrupted)
		return (close(pipe_fd[0]), 1);
	return (0);
}

int	handle_heredoc_redir(t_cmd *cmd, int *i, int k)
{
	if (handle_heredoc(cmd, cmd->word[k][*i + 1]) == -1)
		return (-1);
	if (cmd->heredoc_interrupted)
	{

		cmd->heredoc_interrupted = 0;
		*i += 2;
		return (0);
	}
	*i += 2;
	return (0);
}
