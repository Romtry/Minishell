/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:04:00 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:33:20 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_token *token, char *input)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	token->tlen = tlen_count(input);
	token->err = 0;
	token->envhead = get_env(1);
	token->word = malloc(sizeof(char *) * (token->tlen + 1));
	token->type = malloc(sizeof(t_type) * (token->tlen + 1));
	while (input[i] && is_sep(input[i]) == 0)
		i++;
	while (c < token->tlen)
	{
		i += malloc_word(token, input + i, c);
		c++;
	}
	token->word[c] = NULL;
	token->type[c] = '\0';
}
