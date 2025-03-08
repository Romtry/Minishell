/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:14:27 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/07 13:42:20 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	writer(char *cmd_name, t_cmd *cmd)
{

	if (ft_strchr(cmd_name, '/'))
	{
		if (access(cmd_name, F_OK) == -1)
		{
			cmd->exit = 1;
			*cmd->exit_stat = 127;
			return ;
		}
		else if (access(cmd_name, X_OK) == -1)
		{
			cmd->exit = 1;
			*cmd->exit_stat = 126;
			return ;
		}
	}
	write(2, "minishell: ", 11);
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, ": command not found\n", 20);
	cmd->exit = 1;
	*cmd->exit_stat = 127;
	return ;
}

static void	execute_command2(t_cmd *tmp_cmd, t_cmd *cmd)
{
	char	*cmd_name;
	char	*cmd_path;
	char	**env;

	cmd_name = tmp_cmd->word[0][0];
	if (is_builtin(cmd_name))
	{
		execute_builtin(tmp_cmd);
		cmd->exit = 1;
		*cmd->exit_stat = 1;
		return ;
	}
	cmd_path = get_command_path(cmd_name);
	if (!cmd_path)
		writer(cmd_name, cmd);
	env = get_env(true);
	execve(cmd_path, tmp_cmd->word[0], env);
	free_array(env);
	perror("minishell: execve");
	free(cmd_path); 
	{
		cmd->exit = 1;
		*cmd->exit_stat = 1;
		return ;
	}
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
		cmd->exit = 1;
		*cmd->exit_stat = EXIT_FAILURE;
	}
	else
		execute_command2(&tmp_cmd, cmd);
}
