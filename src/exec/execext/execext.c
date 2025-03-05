/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:16:01 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/05 11:25:20 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_pid(char *cmd_path, char **envp)
{
	perror("execve");
	free(cmd_path);
	free_array(envp);
	exit(EXIT_FAILURE);
}

void	pid_check(char *cmd_path, t_cmd *cmd)
{
	pid_t	pid;
	char	**envp;
	int		status;

	status = 0;
	envp = get_env(true);
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, cmd->word[0], envp) == -1)
			no_pid(cmd_path, envp);
	}
	else if (pid < 0)
		perror("fork");
	else
	{
		waitpid(pid, &status, 0);
		if ((status & 0x7F) != 0)
			*cmd->exit_stat = 128 + (status & 0x7F);
		else
			*cmd->exit_stat = (status >> 8) & 0xFF;
	}
	free_array(envp);
}

void	err1(t_cmd *cmd, bool b)
{
	char	*command;

	if (b == true)
	{
		write(2, "minishell: command not found\n", 29);
		*cmd->exit_stat = 127;
	}
	else
	{
		command = cmd->word[0][0];
		if (ft_strchr(command, '/'))
		{
			if (access(command, F_OK) == -1)
				*cmd->exit_stat = 127;
			else
				*cmd->exit_stat = 126;
		}
		else
		{
			write(2, command, ft_strlen(command));
			write(2, ": command not found\n", 20);
			*cmd->exit_stat = 127;
		}
	}
}

void	execute_external(t_cmd *cmd)
{
	char	*cmd_path;

	if (!cmd || !cmd->word[0] || !cmd->word[0][0])
		return (err1(cmd, true));
	cmd_path = get_command_path(cmd->word[0][0]);
	if (!cmd_path)
		return (err1(cmd, false));
	pid_check(cmd_path, cmd);
	free(cmd_path);
}
