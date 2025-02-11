#include "minishell.h"

static char **get_env_array(void)
{
    extern char **environ;
    return array_cpy(environ);
}

static t_env *get_env_list(void)
{
    extern char **environ;
    t_env *envhead;
    t_env *temp;
    unsigned int i;

    envhead = ft_lstnew(environ[0]);
    if (!envhead)
        return (NULL);
    temp = envhead;
    i = 1;
    while (environ[i])
    {
        temp->next = ft_lstnew(environ[i]);
        if (!temp->next)
            return (NULL);
        temp = temp->next;
        i++;
    }
    return (envhead);
}

void *get_env(unsigned int n)
{
    if (n == 0)
        return get_env_array();
    return get_env_list();
}

char *get_command_path(char *cmd)
{
    char **envp;
    char **paths;
    char *cmd_path;
    int i;

    if (!cmd || !(envp = get_env(0)))
        return (NULL);
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
        cmd_path = ft_strjoin(ft_strjoin2(paths[i], "/"), cmd);
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
        printf("STDOUT_FILENO before external: %d\n", STDOUT_FILENO);

	char **envp;
    pid_t pid;
    char *cmd_path;
    char **cleaned_args;
    int i;

    if (!cmd || !cmd->word[0] || !cmd->word[0][0])
    {
        printf("minishell: command not found\n");
        return;
    }
    cmd_path = get_command_path(cmd->word[0][0]);
    if (!cmd_path)
    {
        printf("minishell: command not found: %s\n", cmd->word[0][0]);
        return;
    }
    envp = get_env(0);
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
        waitpid(pid, NULL, 0);
    free(cmd_path);
    free_array(envp);
    free(cleaned_args);
}
