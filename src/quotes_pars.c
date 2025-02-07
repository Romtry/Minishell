/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:16:04 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/20 13:18:14 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(t_token *token, unsigned int *i, unsigned int n)
{
	char	*temp;

	if (n == 0)
	{
		*i = *i - 1;
		temp = token->word[*i + 1];
		token->word[*i + 1] = token->word[*i];
		token->word[*i] = temp;
	}
	else
	{
		*i = *i + 1;
		temp = token->word[*i - 1];
		token->word[*i - 1] = token->word[*i];
		token->word[*i] = temp;
	}
}

void	realloc_word(t_token *token, unsigned int *one, unsigned int two)
{
	unsigned int	i2;
	unsigned int	i;
	char			**temp;

	i = -1;
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
	free_word(token);
	token->word = temp;
	get_type(token, *one, two);
}

void	erased_quote(t_token *token, unsigned int *p)
{
	char			**temp;
	unsigned int	i;
	unsigned int	i2;

	if (!(*p > 0 && *p < token->tlen - 1 && token->type[*p - 1] == WORD
		&& token->type[*p + 1] == WORD))
		return(erased_str(token, p));
	if (*p > 0)
		*p -= 1;
	i = -1;
	token->tlen -= 2;
	temp = malloc(sizeof(char *) * (token->tlen + 1));
	while (++i < *p)
		temp[i] = ft_strcpy(token->word[i]);
	temp[i] = ft_strjoin(ft_strcpy(token->word[i]), token->word[i + 2]);
	i2 = i + 1;
	i += 3;
	while (token->word[i])
		temp[i2++] = ft_strcpy(token->word[i++]);
	temp[i2] = NULL;
	free_word(token);
	token->word = temp;
	get_type(token, *p, *p);
}



int	secnd_quote(t_token *token, unsigned int *one, t_type quote)
{
	unsigned int	two;

	two = *one + 1;
	if (token->tlen <= 1 && (ft_strlen(token->word[*one]) % 2) == 1)
		return(free_token(token), print_error(token, 1), 1);
	else if (token->tlen <= 1 && (ft_strlen(token->word[*one]) % 2) == 0)
		return(free_token(token), print_error(token, -1), printf("\n"), 1);
	else if ((ft_strlen(token->word[*one]) % 2) == 0)
		return (erased_quote(token, one), 0);
	while (token->word[two] && token->type[two] != quote)
		two++;
	if (!token->word[two])
		return(print_error(token, 1), 1);
	else if ((ft_strlen(token->word[two]) % 2) == 0)
		return (erased_quote(token, &two),
				secnd_quote(token, one, quote));
	else
		return(realloc_word(token, one, two), 0);
}
