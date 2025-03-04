/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:16:01 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/04 09:44:56 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_path(char *cmd)
{
	char	**envp;
	char	**paths;
	char	*cmd_path;
	int		i;
	DIR		*dir;

	if (!cmd || !(envp = get_env(true)))
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1)
		{
			write(2, "minishell: ", 11);
			write(2, cmd, ft_strlen(cmd));
			write(2, ": No such file or directory\n", 28);
			free_array(envp);
			return (NULL);
		}
		dir = opendir(cmd);
		if (dir != NULL)
		{
			closedir(dir);
			write(2, "minishell: ", 11);
			write(2, cmd, ft_strlen(cmd));
			write(2, ": Is a directory\n", 17);
			free_array(envp);
			return (NULL);
		}
		if (access(cmd, X_OK) == -1)
		{
			write(2, "minishell: ", 11);
			write(2, cmd, ft_strlen(cmd));
			write(2, ": Permission denied\n", 20);
			free_array(envp);
			return (NULL);
		}
		free_array(envp);
		return (ft_strndup(cmd, ft_strlen(cmd)));
	}
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (free_array(envp), NULL);
	paths = ft_split(envp[i] + 5, ':');
	free_array(envp);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(ft_strjoin(paths[i], "/", false), cmd, true);
		if (!cmd_path)
			continue ;
		if (access(cmd_path, X_OK) == 0)
			return (free_array(paths), cmd_path);
		free(cmd_path);
	}
	return (free_array(paths), NULL);
}

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
