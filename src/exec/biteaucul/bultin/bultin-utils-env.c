# include "minishell.h"

// Définition globale
t_env   *env_head = NULL;

t_env **get_env_head(void)
{
    static t_env *env_head = NULL;

    if (env_head == NULL)
    {
        extern char **__environ;
        t_env   *new_var;
        char    *equal_sign;
        char    *name;
        char    *value;
        int     i;
        int     duplicate_found;
        t_env   *existing;

        i = 0;
        while (__environ[i])
        {
            equal_sign = ft_strchr(__environ[i], '=');
            if (equal_sign)
            {
                name = ft_strndup(__environ[i], equal_sign - __environ[i]);
                value = ft_strdup(equal_sign + 1);
            }
            else
            {
                name = ft_strdup(__environ[i]);
                value = ft_strdup("");
            }
            duplicate_found = 0;
            existing = env_head;
            while (existing)
            {
                if (ft_strcmp(existing->name, name) == 0)
                {
                    free(name);
                    free(value);
                    duplicate_found = 1;
                    break;
                }
                existing = existing->next;
            }
            if (duplicate_found == 0)
            {
                new_var = malloc(sizeof(t_env));
                if (!new_var)
                {
                    perror("malloc");
                    free(name);
                    free(value);
                    return (NULL);
                }
                new_var->name = name;
                new_var->value = value;
                new_var->next = env_head;
                env_head = new_var;
            }
            i++;
        }
    }
    return (&env_head);
}

void sync_env_with_system(void)
{
    t_env *current;
    int count;
    int i;

    count = 0;
    current = *get_env_head();
    while (current)
    {
        count++;
        current = current->next;
    }
    char **new_environ = malloc(sizeof(char *) * (count + 1));
    if (!new_environ)
    {
        perror("malloc");
        return;
    }
    current = *get_env_head();
    i = 0;
    while (current)
    {
        new_environ[i] = ft_strjoin2(current->name, "=");
        new_environ[i] = ft_strjoin2(new_environ[i], current->value);
        current = current->next;
        i++;
    }
    new_environ[i] = NULL;
    extern char **__environ;
    __environ = new_environ;
}