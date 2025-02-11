# include "minishell.h"

void cd(t_cmd *cmd)
{
    char    *path;
    t_env   *home_env;
    int     i;

    i = 1;
    while (cmd->word[0][i] && ft_strcmp(cmd->word[0][i], " ") == 0)
        i++;
    if (!cmd->word[0][i])
    {
        home_env = get_env(1);
        while (home_env && ft_strcmp(home_env->name, "HOME") != 0)
            home_env = home_env->next;
        if (!home_env)
        {
            printf("minishell: cd: HOME not set\n");
            return;
        }
        path = home_env->value;
    }
    else
        path = cmd->word[0][i];
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

void env_builtin(void)
{
    t_env *env;

    env = get_env(1);
    if (env == NULL)
    {
        printf("No environment variables found.\n");
        return;
    }
    env = env->next;
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