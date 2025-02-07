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
