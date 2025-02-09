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

// void	skip_quotes(t_token *token, unsigned int *i, unsigned int n)
// {
// 	char	*temp;

// 	if (n == 0)
// 	{
// 		*i = *i - 1;
// 		temp = token->word[*i + 1];
// 		token->word[*i + 1] = token->word[*i];
// 		token->word[*i] = temp;
// 	}
// 	else
// 	{
// 		*i = *i + 1;
// 		temp = token->word[*i - 1];
// 		token->word[*i - 1] = token->word[*i];
// 		token->word[*i] = temp;
// 	}
// }

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

void	switch_dollar(t_token *token, unsigned int one, unsigned int *two)
{
	t_env	*env;

	env = token->envhead;
	while (env->next)
	{
		if (ft_strcmp(token->word[one], env->name) == 0)
		{
			free(token->word[one]);
			token->word[one] = ft_strcpy(env->value);
			return ;
		}
		env = env->next;
	}
	erased_str(token, &one);
	*two -= 1;
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
				{
					erased_str(token, &i);
					erased_str(token, &i);
					*one -= 1;
				}
			}
			else
				break;
			*two -= 1;
		}
	}
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
	else if (quote == DQUOTE)
		dollar_indquote(token, one, &two);
	if (*one != two)
		realloc_word(token, one, two);
	return (0);
}
