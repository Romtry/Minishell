/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:00:30 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/19 10:42:47 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}

void	free_cmd(t_cmd	*cmd)
{
	unsigned int	i;

	i = 0;
	while (cmd->word[i])
	{
		free_array(cmd->word[i]);
		free(cmd->type[i]);
		i++;
	}
	free(cmd->type);
	free(cmd->word);
	free(cmd->old_environ);
	free(cmd);
}

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

void	free_token(t_token *token)
{
	if (token->word)
	{
		free_word(token);
		free(token->type);
		token->type = NULL;
		if (token->envhead)
			free_env(token->envhead);
	}
}

void	free_word(t_token *token)
{
	unsigned int	i;

	i = 0;
	if (token->word)
	{
		while (token->word[i])
		{
			free(token->word[i]);
			i++;
		}
		free(token->word);
		token->word = NULL;
	}
}
