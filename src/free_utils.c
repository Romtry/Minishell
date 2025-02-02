/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:01:20 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/24 14:15:10 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	free_cmd(t_cmd	*cmd)
{
	unsigned int	i;
	unsigned int	i2;

	i = 0;
	i2 = 0;
	while (cmd->word[i])
	{
		while (cmd->word[i][i2])
		{
			free(cmd->word[i][i2]);
			i2++;
		}
		free(cmd->word[i]);
		free(cmd->type[i]);
		i2 = 0;
		i++;
	}
	free(cmd->type);
	free(cmd->word);
	free(cmd);
}

void	free_token(t_token *token)
{
	if (token->word)
	{
		free_word(token);
		free(token->type);
		token->type = NULL;
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


void	free_env(t_token *token)
{
	t_env	*temp;

	while (token->envhead)
	{
		temp = token->envhead->next;
		free(token->envhead->name);
		free(token->envhead->value);
		free(token->envhead);
		token->envhead = temp;
	}
	free(token);
}

void	free_array(char **arr)
{
	unsigned int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}