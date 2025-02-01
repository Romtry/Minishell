# include "minishell.h"

char	**get_env(void)
{
	char    **env;

	env = array_cpy(ENV);
	return (env);
}

char	*get_command_path(char *cmd, char **envp)
{
	int     i;
	char**  paths;
	char*   cmd_path;
	char*   temp;

	if (!cmd || !envp)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths && paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(cmd_path, X_OK) == 0)
		{
			free_array(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

void	execute_external(t_cmd *cmd, char **envp)
{
	pid_t   pid;
	char*   cmd_path;

	cmd_path = get_command_path(cmd->word[0][0], envp);
	if (!cmd_path)
	{
		printf("minishell: command not found: %s\n", cmd->word[0][0]);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, cmd->word[0], envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("fork");
	else
		waitpid(pid, NULL, 0);
	free(cmd_path);
}