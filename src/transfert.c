/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:58:06 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/23 14:07:02 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	malloc_array(t_token *token, t_cmd *cmd)
{
	unsigned int	i;
	unsigned int	i2;

	i = 0;
	while (token->word[i])
	{
		while (token->word[i] && token->type[i] != PIPE)
			i2++;
		cmd->word[i] = malloc(sizeof(char *) * (i2 + 1));
		i++;
		i2 = 0;
	}
}

void	transfert2(t_token *token, t_cmd *cmd)
{
	unsigned int	i;
	unsigned int	p;
	unsigned int	i2;

	i = -1;
	p = 0;
	i2 = 0;
	while (token->word[++i])
	{
		malloc_array(token, cmd);
		if (token->type[i] != PIPE)
		{
			cmd->word[p][i2] = token->word[i];
			cmd->type[p][i2] = token->type[i];
			i2++;
		}
		else
		{
			cmd->word[p][i2] = NULL;
			cmd->type[p][i2] = '\0';
			p++;
			i2 = 0;
		}
	}
	cmd->word[p] = NULL;
	cmd->type[p] = NULL;
}

void    transfert(t_token *token, t_cmd	*cmd)
{
    unsigned int    i;
    unsigned int    p;

    i = 0;
    p = 1;
    while (token->word[i])
    {
		if (token->type[i] == PIPE)
			p++;
		i++;
    }
	if (p == 1)
		return;
	cmd->word = malloc(sizeof(char **) * (p + 1));
	cmd->type = malloc(sizeof(unsigned int *) * (p + 1));
	transfert2(token, cmd);
	free_token(token);
}
