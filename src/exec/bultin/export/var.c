/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:04:08 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/07 16:57:55 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	var_init(t_cmd *cmd, char *name, char *value)
{
	t_env	*current;

	current = *cmd->env_head_ptr;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strndup(value, ft_strlen(value));
			return (false);
		}
		current = current->next;
	}
	return (true);
}

void	var_work(t_cmd *cmd, char *name, char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		perror("malloc");
		free(name);
		free(value);
		return ;
	}
	new_var->name = ft_strndup(name, ft_strlen(name));
	new_var->value = ft_strndup(value, ft_strlen(value));
	new_var->next = *cmd->env_head_ptr;
	*cmd->env_head_ptr = new_var;
}
