# include "minishell.h"

void	echo(t_cmd *cmd)
{
	int	i;
	int	n_line;

	i = 1;
	n_line = 1;
	if (cmd->word[0][1] && ft_strcmp(cmd->word[0][1], "-n") == 0)
	{
		n_line = 0;
		i++;
	}
	while (cmd->word[0][i])
	{
		printf("%s", cmd->word[0][i]);
		if (cmd->word[0][i + 1])
			printf(" ");
		i++;
	}
	if (n_line)
		printf("\n");
}

void	cd(t_cmd *cmd, t_env *env)
{
	char	*path;
	t_env	*home_env;

	if (!cmd->word[0][1])
	{
		home_env = env;
		while (home_env && ft_strcmp(home_env->name, "HOME") != 0)
			home_env = home_env->next;
		if (!home_env)
		{
			printf("minishell: cd: HOME not set\n");
			return ;
		}
		path = home_env->value;
	}
	else
		path = cmd->word[0][1];

	if (chdir(path) != 0)
		perror("minishell: cd");
}

void	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("minishell: pwd");
	else
	{
		printf("%s\n", cwd);
		free(cwd);
	}
}

void	ft_export(t_cmd *cmd, t_env **env)
{
	int		i;
	t_env	*new_var;
	t_env	*current;

	if (!cmd->word[0][1])
	{
		current = *env;
		while (current)
		{
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
			current = current->next;
		}
		return ;
	}
	i = 1;
	while (cmd->word[0][i])
	{
		new_var = ft_lstnew(cmd->word[0][i]);
		if (!new_var)
		{
			perror("minishell: export");
			return ;
		}
		new_var->next = *env;
		*env = new_var;
		i++;
	}
}

void	unset(t_cmd *cmd, t_env **env)
{
	t_env	*prev;
	t_env	*curr;
	int		i;

	i = 1;
	while (cmd->word[0][i])
	{
		prev = NULL;
		curr = *env;
		while (curr)
		{
			if (ft_strcmp(curr->name, cmd->word[0][i]) == 0)
			{
				if (prev)
					prev->next = curr->next;
				else
					*env = curr->next;
				free(curr->name);
				free(curr->value);
				free(curr);
				break;
			}
			prev = curr;
			curr = curr->next;
		}
		i++;
	}
}

void	env_builtin(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

void	exit_shell(void)
{
	printf("exit\n");
	exit(0);
}

void	execute_builtin(t_cmd *cmd, t_env **env)
{
	int saved_stdout = dup(STDOUT_FILENO);

	// if (cmd->has_pipe)
		// dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	if (ft_strcmp(cmd->word[0][0], "echo") == 0)
		echo(cmd);
	else if (ft_strcmp(cmd->word[0][0], "cd") == 0)
		cd(cmd, *env);
	else if (ft_strcmp(cmd->word[0][0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd->word[0][0], "export") == 0)
		ft_export(cmd, env);
	else if (ft_strcmp(cmd->word[0][0], "unset") == 0)
		unset(cmd, env);
	else if (ft_strcmp(cmd->word[0][0], "env") == 0)
		env_builtin(*env);
	else if (ft_strcmp(cmd->word[0][0], "exit") == 0)
		exit_shell();
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}