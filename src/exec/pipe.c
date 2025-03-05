/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:19:21 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/05 12:08:57 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_for_children(pid_t pid)
{
	int		status;
	int		exit_status;

	exit_status = 0;
	waitpid(pid, &status, 0);
	if ((status & 0xFF) == 0)
		exit_status = (status >> 8) & 0xFF;
	else
		exit_status = 128 + (status & 0x7F);
	while ((waitpid(-1, &status, 0)) > 0)
	{
		waitpid(-1, &status, 0);
		if ((status & 0x7F) == 13)
			write(STDERR_FILENO, "minishell: Broken pipe\n", ft_strlen("minishell: Broken pipe\n"));
	}
	return (exit_status);
}

static void	handle_parent(int *input_fd, int pipe_fd[2], int i, int count)
{
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (i < count - 1)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
	else
		*input_fd = STDIN_FILENO;
}

static int	create_pipe(int pipe_fd[2], int need_pipe)
{
	if (need_pipe && pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (0);
	}
	return (1);
}

void	execute_piped_commands(t_cmd *cmd)
{
	int		count;
	int		input_fd;
	int		pipe_fd[2];
	pid_t	pid;
	int		i;

	count = cmd_count(cmd);
	input_fd = STDIN_FILENO;
	i = 0;
	while (i < count)
	{
		if (!create_pipe(pipe_fd, (i < count - 1)))
			return ;
		pid = fork();
		if (pid == -1)
			return ((void)perror("minishell: fork"));
		else if (pid == 0)
			handle_child(i, cmd, input_fd, pipe_fd);
		else
			handle_parent(&input_fd, pipe_fd, i, count);
		i++;
	}
	*cmd->exit_stat = wait_for_children(pid);
}
