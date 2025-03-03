/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erased_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:45:27 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/03 15:05:39 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erased_quote(t_token *token, unsigned int *p)
{
	char			**temp;
	unsigned int	i;
	unsigned int	i2;

	if (!(*p > 0 && *p < token->tlen - 1 && token->type[*p - 1] == WORD
			&& token->type[*p + 1] == WORD))
		return (erased_str(token, p));
	if (*p > 0)
		*p -= 1;
	i = -1;
	token->tlen -= 2;
	temp = malloc(sizeof(char *) * (token->tlen + 1));
	while (++i < *p)
		temp[i] = ft_strcpy(token->word[i]);
	temp[i] = ft_strjoin(ft_strcpy(token->word[i]), token->word[i + 2], true);
	i2 = i + 1;
	i += 3;
	while (token->word[i])
		temp[i2++] = ft_strcpy(token->word[i++]);
	temp[i2] = NULL;
	free_word(token);
	token->word = temp;
	// get_type(token, *p, *p);
}
