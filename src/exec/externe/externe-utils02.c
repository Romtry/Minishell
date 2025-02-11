#include "minishell.h"

static int is_empty_or_spaces(const char *str)
{
    int i;

    i = 0;
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

static char  **clean_arguments(char **args)
{
    int   i;
    int   j;
    char  **cleaned_args;
    int   count;

    count = 0;
    i = 0;
    while (args[i])
    {
        if (!is_empty_or_spaces(args[i]))
            count++;
        i++;
    }
    cleaned_args = malloc(sizeof(char *) * (count + 1));
    if (!cleaned_args)
        return (NULL);
    j = 0;
    i = 0;
    while (args[i])
    {
        if (!is_empty_or_spaces(args[i]))
        {
            cleaned_args[j] = args[i];
            j++;
        }
        i++;
    }
    cleaned_args[j] = NULL;
    return (cleaned_args);
}

