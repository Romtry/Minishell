/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:58:06 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/23 10:16:37 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	transfert2(t_token *token)
{
	unsigned int	i;
	unsigned int	p;
	unsigned int	i2;

	i = -1;
	p = 0;
	i2 = -1;
	while (token->word[i])
	{
		i++;
		i2++;
		while (token->word[i] && token->type[i] != PIPE)
		{
			token->cmd->word[p][i2] = token->word[i];
			token->cmd->type[p][i2] = token->type[i];
			i++;
			i2++;
		}
		i2 = -1;
		token->cmd->word[p][i2] = NULL;
		token->cmd->type[p][i2] = '\0';
		p++;
	}
	token->cmd->word[p] = NULL; 
	token->cmd->type[p] = NULL;
}

void    transfert(t_token *token)
{
    unsigned int    i;
    unsigned int    p;

    i = 0;
    p = 0;
    while (token->word[i])
    {
		if (token->type[i] == PIPE)
			p++;
    }
	token->cmd = malloc(sizeof(char **) * (p + 1));
	transfert2(token);
}
