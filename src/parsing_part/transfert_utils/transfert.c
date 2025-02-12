/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:58:06 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:52:45 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	transfert2(t_token *token, t_cmd *cmd)
{
	unsigned int	i;
	unsigned int	p;
	unsigned int	i2;

	i = -1;
	p = 0;
	i2 = 0;
	malloc_array(token, cmd);
	while (token->word[++i])
	{
		if (token->type[i] == PIPE)
			transfert_pipe(cmd, &p, &i2);
		else
		{
			cmd->word[p][i2] = ft_strcpy(token->word[i]);
			cmd->type[p][i2] = token->type[i];
			i2++;
		}
	}
	cmd->word[p][i2] = NULL;
	cmd->type[p][i2] = '\0';
	p++;
	cmd->word[p] = NULL;
	cmd->type[p] = NULL;
}

void    transfert(t_token *token, t_cmd	*cmd)
{
    unsigned int    i;
    unsigned int    p;

    i = 0;
    p = 1;
	cmd->has_pipe = 0;
    while (token->word[i])
    {
		if (token->type[i] == PIPE)
			p++;
		i++;
    }
	cmd->has_pipe = p;
	if (p == 1)
		return (no_pipe(token, cmd));
	cmd->word = malloc(sizeof(char **) * (p + 1));
	cmd->type = malloc(sizeof(unsigned int *) * (p + 1));
	transfert2(token, cmd);
	free_token(token);
}
