/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sews.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:53:00 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/07 16:52:42 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sews(unsigned int i, t_env *current, t_cmd *cmd)
{
	char			**new_environ;

	new_environ = malloc(sizeof(char *) * (i + 1));
	if (!new_environ)
	{
		perror("malloc");
		return ;
	}
	current = *cmd->env_head_ptr;
	new_environ[i] = NULL;
	i--;
	while (current)
	{
		new_environ[i] = ft_strjoin(current->name, "=", false);
		new_environ[i] = ft_strjoin(new_environ[i], current->value, true);
		current = current->next;
		i--;
	}
	__environ = new_environ;
	if (*cmd->env_change == true)
		free_array(*cmd->old_environ);
	*cmd->env_change = true;
	*cmd->old_environ = new_environ;
}

void	sync_env_with_system(t_cmd *cmd)
{
	t_env			*current;
	unsigned int	i;
	extern char		**__environ;

	i = 0;
	current = *cmd->env_head_ptr;
	while (current)
	{
		i++;
		current = current->next;
	}
	sews(i, current, cmd);
}
