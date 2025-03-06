/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:14:27 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/06 13:52:22 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	writer(char *cmd_name)
{
	write(2, "minishell: ", 11);
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, ": command not found\n", 20);
	exit(127);
}

static void	execute_command2(t_cmd *tmp_cmd)
{
	char	*cmd_name;
	char	*cmd_path;

	cmd_name = tmp_cmd->word[0][0];
	if (is_builtin(cmd_name))
	{
		execute_builtin(tmp_cmd);
		exit(0);
	}
	cmd_path = get_command_path(cmd_name);
	if (!cmd_path)
	{
		if (ft_strchr(cmd_name, '/'))
		{
			if (access(cmd_name, F_OK) == -1)
				exit(127);
			else if (access(cmd_name, X_OK) == -1)
				exit(126);
		}
		writer(cmd_name);
	}
	execve(cmd_path, tmp_cmd->word[0], get_env(true));
	perror("minishell: execve");
	free(cmd_path);
	exit(1);
}

void	handle_child(int i, t_cmd *cmd, int input_fd, int pipe_fd[2])
{
	t_cmd	tmp_cmd;
	int		count;
	int		is_not_last;

	tmp_cmd.word = &cmd->word[i];
	tmp_cmd.type = &cmd->type[i];
	tmp_cmd.env_change = cmd->env_change;
	tmp_cmd.old_environ = cmd->old_environ;
	count = cmd_count(cmd);
	is_not_last = (i < count - 1);
	if (input_fd != STDIN_FILENO)
		dup2(input_fd, STDIN_FILENO);
	if (is_not_last)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (handle_redirections(&tmp_cmd) == -1)
	{
		cmd->exit = true;
		*cmd->exit_stat = EXIT_FAILURE;
	}
	else
		execute_command2(&tmp_cmd);
}
