/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:27:45 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/05 13:24:49 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	malloc_word(t_token *token, char *input, unsigned int c)
{
	unsigned int	i;
	unsigned int	save;

	i = 0;
	save = wich_type(input[0]);
	while (input[i] && save == wich_type(input[i]))
		i++;
	token->word[c] = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (input[i] && save == wich_type(input[i]))
	{
		token->word[c][i] = input[i];
		i++;
	}
	token->type[c] = save;
	token->word[c][i] = '\0';
	return (i);
}

unsigned int	count_word(char *str)
{
	unsigned int	save;
	unsigned int	ret;
	unsigned int	i;

	ret = 0;
	i = 0;
	while (str[i] && is_sep(str[i]) == 0)
		i++;
	while (str[i])
	{
		save = wich_type(str[i]);
		while (str[i] && save == wich_type(str[i]))
			i++;
		if ((!str[i]) && is_sep(str[i - 1]) == 0)
			break;
		ret++;
	}
	return (ret);
}

void	lexer(t_token *token, char *input)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	token->tlen = count_word(input);
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
