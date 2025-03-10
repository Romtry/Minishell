/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:24:33 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/10 16:25:37 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*err(unsigned int i, char *cmd, char **envp)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	if (i == 0)
		write(2, ": No such file or directory\n", 28);
	else if (i == 1)
		write(2, ": Is a directory\n", 17);
	else if (i == 2)
		write(2, ": Permission denied\n", 20);
	free_array(envp);
	return (NULL);
}

char	*gcp(DIR *dir, char *cmd, char **envp)
{
	if (access(cmd, F_OK) == -1)
		return (free_array(envp), err(0, cmd, envp));
	dir = opendir(cmd);
	if (dir != NULL)
	{
		closedir(dir);
		return (free_array(envp), err(1, cmd, envp));
	}
	if (access(cmd, X_OK) == -1)
		return (free_array(envp), err(2, cmd, envp));
	return (free_array(envp), ft_strndup(cmd, ft_strlen(cmd)));
}

char	*gcp2(int i, char **envp, char *cmd)
{
	char	**paths;
	char	*cmd_path;

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

char	*get_command_path(char *cmd)
{
	char	**envp;
	int		i;
	DIR		*dir;

	dir = NULL;
	envp = get_env(true);
	if (!envp)
		return(NULL);
	else if (!cmd)
		return(free_array(envp), NULL);
	if (ft_strchr(cmd, '/'))
		return (gcp(dir, cmd, envp));
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (free_array(envp), NULL);
	return (gcp2(i, envp, cmd));
}
