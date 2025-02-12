/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_inquote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:46:29 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:48:12 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_erased(t_token *token, unsigned int *i, unsigned int *one)
{
	erased_str(token, i);
	erased_str(token, i);
	*one -= 1;
}

void	dollar_indquote(t_token *token, unsigned int *one, unsigned int *two)
{
	unsigned int	i;

	i = *one - 1;
	while (++i < *two)
	{
		if (token->type[i] == DOLLAR)
		{
			if (token->word[i + 1][0] == '?')
				switch_es(token, i);
			else if (token->type[i + 1] == WORD)
			{
				erased_str(token, &i);
				i ++;
				switch_dollar(token, i, two);
				if (*two == *one)
					double_erased(token, &i, one);
			}
			else
				break;
			*two -= 1;
		}
	}
}
