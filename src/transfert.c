/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:58:06 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/05 13:53:32 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	malloc_array(t_token *token, t_cmd *cmd)
{
	unsigned int	i;
	unsigned int	i2;
	unsigned int	i3;

	i = 0;
	i2 = 0;
	i3 = 0;
	while (token->word[i3])
	{
		while (token->word[i3] && token->type[i3] != PIPE)
		{
			i3++;
			i2++;
		}
		cmd->word[i] = malloc(sizeof(char *) * (i2 + 1));
		cmd->type[i] = malloc(sizeof(enum e_type) * (i2 + 1));
		i++;
		if (token->word[i3])
			i3++;
		i2 = 0;
	}
}

void	transfert_pipe(t_cmd *cmd, unsigned int *p, unsigned int *i2)
{
	cmd->word[*p][*i2] = NULL;
	cmd->type[*p][*i2] = '\0';
	*p += 1;
	*i2 = 0;
}

void	transfert2(t_token *token, t_cmd *cmd)
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
	printf("%u\n", cmd->type[1][0]);
}

void	no_pipe(t_token *token, t_cmd *cmd)
{
	unsigned int	i;

	i = 0;
	cmd->word = malloc(sizeof(char **) * (2));
	cmd->type = malloc(sizeof(unsigned int *) * (2));
	cmd->word[0] = array_cpy(token->word);
	cmd->word[1] = NULL;
	while (token->type[i])
		i++;
	cmd->type[0] = malloc(sizeof(enum e_type) * (i + 1));
	i = -1;
	while (token->type[++i] != '\0')
		cmd->type[0][i] = token->type[i];
	cmd->type[0][i] = '\0';
	cmd->type[1] = NULL;
	free_token(token);
}

void    transfert(t_token *token, t_cmd	*cmd)
{
    unsigned int    i;
    unsigned int    p;

    i = 0;
    p = 1;
	cmd->has_pipe = 0;
	// print_token(token);
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
