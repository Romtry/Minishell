/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:20:22 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:20:39 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env->next)
	{
		temp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = temp;
	}
	free(env->name);
	free(env->value);
	free(env);
}
