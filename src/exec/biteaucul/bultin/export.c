# include "minishell.h"

void ft_export(t_cmd *cmd)
{
    int i;
    t_env **env_head_ptr;
    t_env *current;
    t_env *new_var;
    char *name;
    char *value;
    char *equal_sign;

    i = 1;
    env_head_ptr = get_env_head();
    if (!env_head_ptr)
    {
        perror("get_env_head");
        return;
    }
    if (!cmd->word[0][1])
    {
        current = *env_head_ptr;
        while (current)
        {
            printf("declare -x %s=\"%s\"\n", current->name, current->value);
            current = current->next;
        }
        return;
    }
    while (cmd->word[0][i])
    {
        if (ft_strcmp(cmd->word[0][i], " ") == 0)
        {
            i++;
            continue;
        }
        equal_sign = ft_strchr(cmd->word[0][i], '=');
        if (equal_sign)
        {
            name = ft_strndup(cmd->word[0][i], equal_sign - cmd->word[0][i]);
            value = ft_strdup(equal_sign + 1);
        }
        else
        {
            name = ft_strdup(cmd->word[0][i]);
            value = ft_strdup("");
        }
        if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
        {
            char *temp = ft_strndup(value + 1, ft_strlen(value) - 2);
            free(value);
            value = temp;
        }
        current = *env_head_ptr;
        int var_exists = 0;
        while (current)
        {
            if (ft_strcmp(current->name, name) == 0)
            {
                free(current->value);
                current->value = ft_strdup(value);
                var_exists = 1;
                break;
            }
            current = current->next;
        }
        if (!var_exists)
        {
            new_var = malloc(sizeof(t_env));
            if (!new_var)
            {
                perror("malloc");
                free(name);
                free(value);
                return;
            }
            new_var->name = ft_strdup(name);
            new_var->value = ft_strdup(value);
            new_var->next = *env_head_ptr;
            *env_head_ptr = new_var;
        }
        free(name);
        free(value);
        i++;
    }
	sync_env_with_system();
}