/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:06:08 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/10 11:06:33 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd2(void)
{
	t_env	*home_env;
	t_env	*head;
	char	*home;

	home = NULL;
	head = get_env(false);
	home_env = head;
	while (home_env && ft_strcmp(home_env->name, "HOME") != 0)
		home_env = home_env->next;
	if (home_env)
		home = ft_strndup(home_env->value, ft_strlen(home_env->value));
	return (free_env(head), home);
}
