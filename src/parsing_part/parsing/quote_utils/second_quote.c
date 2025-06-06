/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:17:47 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/03 14:56:25 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	secnd_quote(t_token *token, unsigned int *one, t_type quote)
{
	unsigned int	two;

	two = *one + 1;
	if (token->tlen <= 1 && (ft_strlen(token->word[*one]) % 2) == 1)
		return (free_token(token), print_error(token, 1));
	else if (token->tlen <= 1 && (ft_strlen(token->word[*one]) % 2) == 0)
		return (free_token(token), print_error(token, -1),
			(void)printf("\n"));
	else if ((ft_strlen(token->word[*one]) % 2) == 0)
		return (erased_quote(token, one));
	while (token->word[two] && token->type[two] != quote)
		two++;
	if (!token->word[two])
		return (print_error(token, 1));
	else if ((ft_strlen(token->word[two]) % 2) == 0)
		return (erased_quote(token, &two),
			secnd_quote(token, one, quote));
	else if (quote == DQUOTE)
		dollar_indquote(token, one, &two);
	if (*one != two)
		realloc_word(token, one, two);
}
