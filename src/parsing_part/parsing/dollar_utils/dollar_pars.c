/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:02:09 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 13:54:44 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_pars(t_token *token, unsigned int *i)
{
	if (token->word[*i + 1] && token->word[*i + 1][0] == '?')
		switch_es(token, *i);
	else if (*i > 0 && *i + 1 >= token->tlen && token->type[*i - 1] == WORD)
	{
		token->word[*i - 1] = ft_strjoin(token->word[*i - 1], "$", true);
		erased_str(token, i);
	}
	else if (*i + 1 >= token->tlen && (*i == 0 || token->type[*i - 1] != WORD))
		token->type[*i] = WORD;
	else
		pars_dollar(token, *i);
	*i -= 1;
}
