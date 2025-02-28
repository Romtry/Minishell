/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:16:01 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/28 12:25:22 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_path(char *cmd)
{
	char	**envp;
	char	**paths;
	char	*cmd_path;
	int		i;

	if (!cmd || !(envp = get_env(true)))
        return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1)
		{
			write(2, "minishell: ", 11);
			write(2, cmd, ft_strlen(cmd));
			write(2, ": No such file or directory\n", 28);
			return (NULL);
		}
		else if (access(cmd, X_OK) == -1)
		{
			write(2, "minishell: ", 11);
			write(2, cmd, ft_strlen(cmd));
			write(2, ": Permission denied\n", 20);
			return (NULL);
		}
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
			continue;
		if (access(cmd_path, X_OK) == 0)
			return (free_array(paths), cmd_path);
		free(cmd_path);
	}
	return (free_array(paths), NULL);
}

static int is_empty_or_spaces(const char *str)
{
	int i = 0;
	if (!str || str[0] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static char **clean_arguments(char **args)
{
	int i, j;
	char **cleaned_args;
	int count = 0;

	for (i = 0; args[i]; i++)
		if (!is_empty_or_spaces(args[i]))
			count++;
	cleaned_args = malloc(sizeof(char *) * (count + 1));
	if (!cleaned_args)
		return (NULL);
	j = 0;
	for (i = 0; args[i]; i++)
	{
		if (!is_empty_or_spaces(args[i]))
			cleaned_args[j++] = args[i];
	}
	cleaned_args[j] = NULL;
	return cleaned_args;
}

void execute_external(t_cmd *cmd)
{
		// printf("STDOUT_FILENO before external: %d\n", STDOUT_FILENO);
	int		status;
	char 	**envp;
	pid_t	pid;
	char 	*cmd_path;
	char 	**cleaned_args;

	status = 0;
	if (!cmd || !cmd->word[0] || !cmd->word[0][0])
	{
		write(2, "minishell: command not found\n", 29);
		*cmd->exit_stat = 127;
		return;
	}
	cmd_path = get_command_path(cmd->word[0][0]);
	if (!cmd_path)
	{
		write(2, cmd->word[0][0], ft_strlen(cmd->word[0][0]));
		write(2, ": command not found:\n", 21);
		*cmd->exit_stat = 127;
		return;
	}
	envp = get_env(true);
	cleaned_args = clean_arguments(cmd->word[0]);
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, cleaned_args, envp) == -1)
		{
			perror("execve");
			free(cmd_path);
			free_array(envp);
			exit(EXIT_FAILURE);
		}
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
	// printf("exit stat = %d", *cmd->exit_stat);
	free(cmd_path);
	free_array(envp);
	free(cleaned_args);
}
