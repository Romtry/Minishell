/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:37:44 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 10:37:53 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
