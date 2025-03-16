/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttouahmi <ttouahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:14:27 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/16 15:11:15 by ttouahmi         ###   ########.fr       */
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

static void	exec_cmd2_util(t_cmd *cmd, char *cmd_path, char **env)
{
	free_array(env);
	free(cmd_path);
	cmd->exit = 1;
	*cmd->exit_stat = 1;
}

static void	execute_command2(t_cmd *tmp_cmd, t_cmd *cmd)
{
	char	*cmd_name;
	char	*cmd_path;
	char	**env;

	cmd_name = tmp_cmd->word[0][0];
	if (is_builtin(cmd_name))
	{
		cmd->exit = 1;
		*cmd->exit_stat = 1;
		return (execute_builtin(tmp_cmd));
	}
	cmd_path = get_command_path(cmd_name);
	if (!cmd_path && (tmp_cmd->type[0][0] == WORD
		|| tmp_cmd->type[0][0] == SQUOTED || tmp_cmd->type[0][0] == DQUOTED))
		writer(cmd_name, cmd);
	if (cmd->exit != 0)
		return ;
	env = get_env(true);
	if (tmp_cmd->type[0][0] == WORD
		|| tmp_cmd->type[0][0] == SQUOTED || tmp_cmd->type[0][0] == DQUOTED)
	{
		execve(cmd_path, tmp_cmd->word[0], env);
		perror("minishell: execve");
	}
	return (exec_cmd2_util(cmd, cmd_path, env));
}

static t_cmd	cmd_cpy(t_cmd *cmd, int i)
{
	t_cmd	tmp_cmd;

	tmp_cmd.word = &cmd->word[i];
	tmp_cmd.type = &cmd->type[i];
	tmp_cmd.env_change = cmd->env_change;
	tmp_cmd.old_environ = cmd->old_environ;
	tmp_cmd.exit_stat = cmd->exit_stat;
	tmp_cmd.heredoc_fd = cmd->heredoc_fd;
	return (tmp_cmd);
}

void	handle_child(int i, t_cmd *cmd, int input_fd, int pipe_fd[2])
{
	t_cmd	tmp_cmd;
	int		count;
	int		is_not_last;

	tmp_cmd = cmd_cpy(cmd, i);
	count = cmd_count(cmd);
	is_not_last = (i < count - 1);
	if (input_fd != STDIN_FILENO)
		dup2(input_fd, STDIN_FILENO);
	if (is_not_last)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[1]);
	}
	if (handle_redirections(&tmp_cmd) == -1)
	{
		cmd->exit = 1;
		*cmd->exit_stat = EXIT_FAILURE;
		return ;
	}
	else
		execute_command2(&tmp_cmd, cmd);
	exit(*cmd->exit_stat);
}
