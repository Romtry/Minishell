/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sews.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:53:00 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/24 12:10:58 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sync_env_with_system(t_cmd *cmd)
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
		new_environ[i] = ft_strjoin(current->name, "=", false);
		new_environ[i] = ft_strjoin(new_environ[i], current->value, true);
		current = current->next;
		i++;
	}
	new_environ[i] = NULL;
	extern char **__environ;
	__environ = new_environ;
	if (*cmd->env_change == true)
		free_array(*cmd->old_environ);
	*cmd->env_change = true;
	*cmd->old_environ = new_environ;
}
