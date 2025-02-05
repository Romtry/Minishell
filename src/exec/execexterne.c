# include "minishell.h"

void	*get_env(unsigned int n)
{
	char    		**env;
	unsigned int	i;
	t_env			*envhead;
	t_env			*temp;

	env = array_cpy(ENV);
	if (n == 0)
		return (env);
	i = 0;
	envhead = ft_lstnew(ENV[0]);
	temp = envhead;
	while (ENV[i])
	{
		temp->next = ft_lstnew(ENV[i]);
		temp = temp->next;
		i++;
	}
	free_array(env);
	return (envhead);
}

char	*get_command_path(char *cmd)
{
	char	**envp;
	int     i;
	char**  paths;
	char*   cmd_path;

	envp = get_env(0);
	if (!cmd || !envp)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	free_array(envp);
	i = 0;
	while (paths && paths[i])
	{
		cmd_path = ft_strjoin(ft_strjoin2(paths[i], "/"), cmd);
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

void	execute_external(t_cmd *cmd)
{
	char	**envp;
	pid_t   pid;
	char*   cmd_path;

	envp = get_env(0);
	cmd_path = get_command_path(cmd->word[0][0]);
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
	free_array(envp);
	free(cmd_path);
}
