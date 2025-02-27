/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sews.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:53:00 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/27 13:28:38 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sync_env_with_system(t_cmd *cmd)
{
	t_env *current;
	int i;

	i = 0;
	current = *get_env_head();
	while (current)
	{
		i++;
		current = current->next;
	}
	char **new_environ = malloc(sizeof(char *) * (i + 1));
	if (!new_environ)
	{
		perror("malloc");
		return;
	}
	current = *get_env_head();
	new_environ[i] = NULL;
	i--;
	while (current)
	{
		new_environ[i] = ft_strjoin(current->name, "=", false);
		new_environ[i] = ft_strjoin(new_environ[i], current->value, true);
		current = current->next;
		i--;
	}
	extern char **__environ;
	__environ = new_environ;
	if (*cmd->env_change == true)
		free_array(*cmd->old_environ);
	*cmd->env_change = true;
	*cmd->old_environ = new_environ;
}
