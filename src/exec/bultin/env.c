/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:37:44 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/14 08:03:39 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void env_builtin(void)
{
	t_env   *env;
	t_env	*head;

	env = get_env(false);
	head = env;
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
	free_env(head);
}
