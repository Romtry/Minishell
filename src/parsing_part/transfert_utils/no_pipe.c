/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:52:24 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:52:31 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
