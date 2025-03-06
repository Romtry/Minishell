/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:49:55 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/06 14:29:08 by rothiery         ###   ########.fr       */
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
	if (handle_fd_dup(pipe_fd[0], STDIN_FILENO) == -1)
		return (close(pipe_fd[0]), -1);
	close(pipe_fd[0]);
	if (cmd->heredoc_interrupted)
		return (1);
	else
		return (0);
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

int	process_redir(t_cmd *cmd, int *i, int *j, char **new_args)
{
	if (!ft_strcmp(cmd->word[0][*i], ">>")
		|| !ft_strcmp(cmd->word[0][*i], ">"))
		return (handle_out_redir(cmd, i));
	if (!ft_strcmp(cmd->word[0][*i], "<<"))
		return (handle_heredoc_redir(cmd, i));
	if (!ft_strcmp(cmd->word[0][*i], "<"))
		return (handle_in_redir(cmd, i));
	new_args[(*j)++] = ft_strndup(cmd->word[0][*i],
			ft_strlen(cmd->word[0][*i]));
	(*i)++;
	return (0);
}

void	determine_redirection_params(int append, int *flags,
		const char **redir_type)
{
	if (append)
	{
		*flags |= O_APPEND;
		*redir_type = "append";
	}
	else
	{
		*flags |= O_TRUNC;
		*redir_type = "output";
	}
}
