# include "minishell.h"

void    echo(t_cmd *cmd)
{
    int     i;
    int     n_line;

    i = 1;
    n_line = 1;
    while (cmd->word[0][i] && ft_strcmp(cmd->word[0][i], " ") == 0)
        i++;
    if (cmd->word[0][i] && is_n_option(cmd->word[0][i]))
    {
        n_line = 0;
        i++;
    }
    while (cmd->word[0][i])
    {
        if (ft_strcmp(cmd->word[0][i], " ") != 0)
        {
            printf("%s", cmd->word[0][i]);
            if (cmd->word[0][i + 1] && ft_strcmp(cmd->word[0][i + 1], " ") == 0)
                printf(" ");
        }
        i++;
    }
    if (n_line)
        printf("\n");
}

void cd(t_cmd *cmd)
{
    char *path;
    t_env *home_env;
    int i = 1;

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

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    char *d;
    const char *s;

    d = dest;
    s = src;
    while (n--)
        *d++ = *s++;
    return dest;
}

char *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    if ((char)c == '\0')
        return (char *)s;
    return NULL;
}
char *ft_strndup(const char *s, size_t n)
{
    char *dup;
    size_t len;

    len = 0;
    while (s[len] && len < n)
        len++;
    dup = (char *)malloc(len + 1);
    if (!dup)
        return NULL;
    ft_memcpy(dup, s, len);
    dup[len] = '\0';
    return dup;
}

char *ft_strdup(const char *s)
{
    char *dup;
    size_t len;

    len = ft_strlen(s);
    dup = (char *)malloc(len + 1);
    if (!dup)
        return NULL;
    ft_memcpy(dup, s, len + 1);
    return dup;
}

t_env *env_head = NULL;


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



void remove_duplicates_from_env_head(void)
{
    t_env *current = *get_env_head();
    t_env *prev = NULL;
    t_env *temp;

    while (current)
    {
        temp = *get_env_head();
        while (temp != current)
        {
            if (ft_strcmp(temp->name, current->name) == 0)
            {
                if (prev)
                    prev->next = current->next;
                else
                    *get_env_head() = current->next;
                free(current->name);
                free(current->value);
                free(current);
                current = prev ? prev->next : *get_env_head();
                break;
            }
            temp = temp->next;
        }
        if (temp == current)
        {
            prev = current;
            current = current->next;
        }
    }
}

//j'ai refait avec while, je renvoie dans l'autrefichier
void remove_duplicates_from_environ(void)
{
    extern char **__environ;
    int i, j, k;

    for (i = 0; __environ[i]; i++)
    {
        for (j = i + 1; __environ[j]; j++)
        {
            if (ft_strcmp(__environ[i], __environ[j]) == 0)
            {
                free(__environ[j]);
                for (k = j; __environ[k]; k++)
                {
                    __environ[k] = __environ[k + 1];
                }
                j--;
            }
        }
    }
}

void sync_env_with_system(void)
{
    t_env *current;
    int count = 0;
    int i;

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

void ft_export(t_cmd *cmd)
{
    int i = 1;
    t_env **env_head_ptr;
    t_env *current;
    t_env *new_var;
    char *name;
    char *value;
    char *equal_sign;

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

void unset(t_cmd *cmd)
{
    t_env **env_head_ptr;
    t_env *prev;
    t_env *curr;
    int i;

    env_head_ptr = get_env_head();
    if (!env_head_ptr)
    {
        perror("get_env_head");
        return;
    }

    i = 1;
    while (cmd->word[0][i])
    {
        if (ft_strcmp(cmd->word[0][i], " ") == 0)
        {
            i++;
            continue;
        }
        char *var_name = cmd->word[0][i];
        char *equal_sign = ft_strchr(var_name, '=');
        if (equal_sign)
        {
            var_name = ft_strndup(var_name, equal_sign - var_name);
        }
        prev = NULL;
        curr = *env_head_ptr;
        while (curr)
        {
            if (ft_strcmp(curr->name, var_name) == 0)
            {
                if (prev)
                    prev->next = curr->next;
                else
                    *env_head_ptr = curr->next;
                free(curr->name);
                free(curr->value);
                free(curr);
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        if (equal_sign)
            free(var_name);

        i++;
    }
	sync_env_with_system();
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
    while (env)
    {
        printf("%s=%s\n", env->name, env->value);
        env = env->next;
    }
}

unsigned int	exit_util(char *str, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (2);
		i++;
	}
	if (n == 0)
		return(256 - (char_int(str) % 256));
	else
		return(char_int(str) % 256);
}

void	exit_shell(t_cmd *cmd)
{
	if (cmd->word[0][2])
	{
		if (cmd->word[0][1][0] == '-')
			*cmd->exit_stat = exit_util(cmd->word[0][2], 0);
	}
		else
			*cmd->exit_stat = exit_util(cmd->word[0][1], 1);
	printf("exit\n");
	exit(*cmd->exit_stat);
}

void	execute_builtin(t_cmd *cmd)
{
	// printf("STDOUT_FILENO before builtin: %d\n", STDOUT_FILENO);

	if (ft_strcmp(cmd->word[0][0], "echo") == 0)
		echo(cmd);
	else if (ft_strcmp(cmd->word[0][0], "cd") == 0)
		cd(cmd);
	else if (ft_strcmp(cmd->word[0][0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd->word[0][0], "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd->word[0][0], "unset") == 0)
		unset(cmd);
	else if (ft_strcmp(cmd->word[0][0], "env") == 0)
		env_builtin();
	else if (ft_strcmp(cmd->word[0][0], "exit") == 0)
		exit_shell();
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
