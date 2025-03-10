/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:37:12 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/10 09:56:54 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset2(t_cmd *cmd, char *var_name)
{
	t_env	*prev;
	t_env	*curr;

	prev = (NULL);
	curr = *cmd->env_head_ptr;
	while (curr)
	{
		if (ft_strcmp(curr->name, var_name) == 0)
		{
			*cmd->exit_stat = 0;
			if (prev)
				prev->next = curr->next;
			else
				*cmd->env_head_ptr = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	unset(t_cmd *cmd)
{
	char	*var_name;
	char	*equal_sign;
	int		i;

	if (!cmd->env_head_ptr)
		return ;
	i = 1;
	while (cmd->word[0][i])
	{
		var_name = cmd->word[0][i];
		equal_sign = ft_strchr(var_name, '=');
		if (equal_sign)
			var_name = ft_strndup(var_name, equal_sign - var_name);
		unset2(cmd, var_name);
		if (equal_sign)
			free(var_name);
		i++;
	}
	sync_env_with_system(cmd);
}
