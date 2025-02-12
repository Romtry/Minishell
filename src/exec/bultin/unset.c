/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:37:12 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 10:37:29 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
