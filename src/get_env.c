/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:10:58 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:11:34 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
