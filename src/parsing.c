/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:55:42 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/31 15:13:00 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_pars(t_token *token, unsigned int i)
{
	if (token->word[i - 2] && (token->type[i - 2] == WORD
		|| token->type[i - 2] == DOLLAR || token->word[i - 2] == NULL))
		return ;
	else if (token->word[i + 2] && (token->type[i + 2] == WORD
		|| token->type[i + 2] == DOLLAR || token->word[i + 2] == NULL))
		return ;
	print_error(2);
}

void	parsing(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->word[i])
	{
		if (token->type[i] == SINGLEQUOTE || token->type[i] == DOUBLEQUOTE)
			secnd_quote(token, &i, token->type[i]);
		else if (token->type[i] == PIPE)
			pipe_pars(token, i);
		// else if (token->type[i] == DOLLAR)
		i++;
	}
}
// mais si je met 'et un truc du genre cette phrase
