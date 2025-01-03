/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:55:42 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/03 10:20:14 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_pars(t_token *token, unsigned int i)
{
	
	if (i == 0 || i == token->tlen - 1)
		return (print_error(token, 2));
	else if (ft_strlen(token->word[i]) != 1)
		return (print_error(token, 2));
	else if (token->type[i - 1] == WORD || token->type[i - 1] == DOLLAR)
	{
		if (token->type[i + 1] == WORD || token->type[i + 1] == DOLLAR
			|| token->type[i + 1] == SINGLEQUOTE || token->type[i + 1] == DOUBLEQUOTE)
			return ;
	}
	print_error(token, 2);
}

unsigned int	parsing(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->word[i])
	{
		if (token->type[i] == SINGLEQUOTE || token->type[i] == DOUBLEQUOTE)
			secnd_quote(token, &i, token->type[i]);
		if (token->err == 1)
			return (1);
		if (i > 0 && token->type[i - 1]  == SEP)
		{
			i--;
			erased_str(token, &i);
		}
		i++;
		print_token(token);
		printf("\n");
	}
	i--;
	if (token->word[i] && token->type[i] == SEP)
		erased_str(token, &i);
	print_token(token);
	i = 0;
	while (token->word[i])
	{
		if (token->type[i] == PIPE)
			pipe_pars(token, i);
		// else if (token->type[i] == DOLLAR)
		i++;
	}
	return (0);
}
// mais si je met 'et un truc du genre cette phrase
