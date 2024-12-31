/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:16:04 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/31 15:36:58 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(t_token *token, unsigned int i, unsigned int n)
{
	char	*temp;

	if (n == 0)
	{
		i = i - 1;
		temp = token->word[i + 1];
		token->word[i + 1] = token->word[i];
		token->word[i] = temp;
	}
	else
	{
		i = i + 1;
		temp = token->word[i - 1];
		token->word[i - 1] = token->word[i];
		token->word[i] = temp;
	}
}

void	realloc_word(t_token *token, unsigned int *one, unsigned int two)
{
	unsigned int	i2;
	unsigned int	i;
	char			**temp;

	i = -1;
	if (*one != 0 && token->type[*one - 1] == WORD)
		skip_quotes(token, *one, 0);
	if (token->word[two + 1] && token->type[two + 1] == WORD)
		skip_quotes(token, two, 1);
	token->tlen -= (two - *one);
	print_token(token);
	printf("\n");
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

void	erased2(t_token *token, unsigned int p)
{
	
}

void	erased_str(t_token *token, unsigned int *p)
{
	char			**temp;
	unsigned int	i;
	unsigned int	i2;

	i = -1;
	if (p > 0 && p < token->tlen && token->type[p - 1] == WORD
		&& token->type[p-- + 1] == WORD)
		token->tlen--;
	token->tlen--;
	temp = malloc(sizeof(char *) * (token->tlen + 1));
	while (++i < *p)
		temp[i] = ft_strcpy(token->word[i]);
	if (*p > 0 && *p <= token->tlen && token->type[*p - 1] == WORD
		&& token->type[*p + 1] == WORD)
		temp[i - 1] = ft_strjoin(temp[i - 1], token->word[i + 1]);
	i2 = i;
	while (i < token->tlen)
		temp[i2++] = ft_strcpy(token->word[i++]);
	temp[i2] = NULL;
	*p -= 1;
	free_token(token);
	token->word = temp;
	get_type(token);
}

int	secnd_quote(t_token *token, unsigned int *one, t_type quote)
{
	unsigned int	two;

	two = *one + 1;
	if (token->tlen <= 1 && (ft_strlen(token->word[*one]) % 2) == 1)
		return(print_error(1), 1);
	else if (token->tlen <= 1 && (ft_strlen(token->word[*one]) % 2) == 0)
		return(print_error(0), 1);
	else if ((ft_strlen(token->word[*one]) % 2) == 0)
		return (erased_str(token, one), 0);
	while (token->word[two] && token->type[two] != quote)
		two++;
	if ((ft_strlen(token->word[two]) % 2) == 0)
		return (erased_str(token, &two),
				secnd_quote(token, one, quote));
	else if (token->word[two])
		return(realloc_word(token, one, two), 0);
	else
		return(print_error(1), 1);
}
