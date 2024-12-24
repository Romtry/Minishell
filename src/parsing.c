/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:55:42 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/24 15:20:58 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quote(t_token *token)
{
	
}

void	realloc_word(t_token *token, unsigned int *one, unsigned int two)
{
	unsigned int	i2;
	unsigned int	i;
	char			**temp;

	i = -1;
	if (*one != 0 && token->type[*one - 1] == WORD)
		*one = *one -1;
	if (token->word[two + 1] && token->word[two + 1] == WORD)
		two++;
	token->tlen -= (two - *one);
	temp = malloc(sizeof(char *) * (token->tlen + 1));
	while (++i < *one)
		temp[i] = ft_strcpy(token->word[i]);
	i2 = i++;
	temp[i2] = ft_strcpy(token->word[i]);
	while (++i < two)
		temp[i2] = ft_strjoin(temp[i2], token->word[i]);
	while (token->word[++i])
		temp[++i2] = ft_strcpy(token->word[i]);
	temp[i2 + 1] = NULL;
	free_token(token);
	token->word = temp;
	get_type(token);
}

int	secnd_quote(t_token *token, unsigned int *one)
{
	unsigned int	two;

	two = *one + 1;
	while (token->word[two] && token->type[two] != SINGLEQUOTE)
		two++;
	// printf("two = %u\n", two);
	if (token->word[two])
		return(realloc_word(token, one, two), 0);
	else
		return(print_error(1), 1);
}

void	parsing(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->word[i])
	{
		if (token->type[i] == SINGLEQUOTE)
			secnd_quote(token, &i);
		i++;
	}
}
// mais si je met 'et un truc du genre cette phrase
