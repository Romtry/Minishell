/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:35:49 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/25 11:29:56 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
