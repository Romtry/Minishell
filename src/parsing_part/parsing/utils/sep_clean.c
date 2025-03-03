/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:22:21 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/28 09:20:35 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sep_clean(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->word[i])
	{
		if (token->word[i + 1] && (token->type[i] == WORD
				|| token->type[i] == SQUOTED || token->type[i] == DQUOTED)
			&& (token->type[i + 1] == WORD || token->type[i + 1] == SQUOTED
				|| token->type[i + 1] == DQUOTED))
		{
			token->word[i] = ft_strjoin(token->word[i], token->word[i + 1], true);
			i++;
			erased_str(token, &i);
		}
		if (token->type[i] == SEP)
			erased_str(token, &i);
		i++;
	}
}
