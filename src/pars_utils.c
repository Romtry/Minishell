/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:34:52 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/20 13:31:10 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erased_str2(t_token *token, unsigned int s)
{
	char			**temp;
	unsigned int	i;
	unsigned int	i2;

	i = -1;
	token->tlen--;
	if (token->tlen == 0)
	{
		token->err = 1;
		return ;
	}
	temp = malloc(sizeof(char *) * (token->tlen + 1));
	while (++i < s)
		temp[i] = ft_strcpy(token->word[i]);
	i2 = i;
	i++;
	while (token->word[i])
		temp[i2++] = ft_strcpy(token->word[i++]);
	temp[i2] = NULL;
	free_word(token);
	token->word = temp;
	get_type(token, s, s);
}

void	erased_str(t_token *token, unsigned int *s)
{
	char			**temp;
	unsigned int	i;
	unsigned int	i2;

	i = -1;
	token->tlen--;
	if (token->tlen == 0)
	{
		token->err = 1;
		return ;
	}
	temp = malloc(sizeof(char *) * (token->tlen + 1));
	while (++i < *s)
		temp[i] = ft_strcpy(token->word[i]);
	i2 = i;
	i++;
	while (token->word[i])
		temp[i2++] = ft_strcpy(token->word[i++]);
	temp[i2] = NULL;
	free_word(token);
	token->word = temp;
	get_type(token, *s, *s);
	if (*s > 0)
		*s -= 1;
}

void	quote_type(t_token *token, unsigned int one, unsigned int *temp)
{
	if (token->type[one] == DQUOTE)
		temp[one] = DQUOTED;
	else if (token->type[one] == SQUOTE)
		temp[one] = SQUOTED;
}

void	get_type(t_token *token, unsigned int one, unsigned int two)
{
	unsigned int	i;
	unsigned int	i2;
	unsigned int	*temp;

	i = -1;
	temp = malloc(sizeof(unsigned int) * (token->tlen + 1));
	while (token->word[++i] && i < one)
		temp[i] = token->type[i];
	if (one != two)
	{
		quote_type(token, one, temp);
		i2 = i + 1;
	}
	else
		i2 = i;
	i = two + 1;
	while (token->word[i2])
	{
		temp[i2] = token->type[i];
		i2++;
		i++;
	}
	temp[i2] = '\0';
	free(token->type);
	token->type = temp;
}

void	pars_dollar(t_token *token, unsigned int i)
{
	t_env	*list;

	list = token->envhead;
	while (list)
	{
		if (ft_strcmp(list->name, token->word[i + 1]) == 0
			&& token->type[i + 1] == WORD)
		{
			erased_str(token, &i);
			if (i == 0)
				i--;
			free(token->word[i + 1]);
			token->word[i + 1] = ft_strcpy(list->value);
			return ;
		}
		list = list->next;
	}
	if (i < token->tlen && token->type[i + 1] == WORD)
		erased_str2(token, i);
	else if (i < token->tlen && i > 0
		&& token->type[i - 1] == WORD && token->type[i + 1] != WORD)
		token->word[i - 1] = ft_strjoin(token->word[i - 1], "$");
	else if (token->type[i + 1] == DQUOTED || token->type[i + 1] == SQUOTED)
		token->word[i + 1] = ft_strjoin2("$", token->word[i + 1]);
	erased_str(token, &i);
	token->type[i] = WORD;
}
