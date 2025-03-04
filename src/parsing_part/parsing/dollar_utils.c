/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:29:19 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/04 10:04:30 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	switch_es(t_token *token, unsigned int i)
{
	char	*temp;

	erased_str(token, &i);
	if (token->word[i][0] != '?')
		i++;
	if (token->word[i][1])
	{
		temp = ft_strcpy(token->word[i] + 1);
		free(token->word[i]);
		token->word[i] = num_char(*token->exit_stat);
		token->word[i] = ft_strjoin(token->word[i], temp, true);
		free(temp);
	}
	else
	{
		free(token->word[i]);
		token->word[i] = num_char(*token->exit_stat);
	}
	if (i > 0 && token->type[i - 1] == WORD)
	{
		token->word[i - 1] = ft_strjoin(token->word[i - 1],
				token->word[i], true);
		erased_str(token, &i);
	}
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

void	pars_dollar(t_token *token, unsigned int i)
{
	t_env	*list;

	list = token->envhead;
	while (list)
	{
		if (ft_strcmp(list->name, token->word[i + 1]) == 0)
		{
			erased_str(token, &i);
			if (i == 0 && token->tlen == 1)
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
		token->word[i - 1] = ft_strjoin(token->word[i - 1], "$", true);
	else if (token->type[i + 1] == DQUOTED || token->type[i + 1] == SQUOTED)
		token->word[i + 1] = ft_strjoin("$", token->word[i + 1], false);
	erased_str(token, &i);
}

char	*num_char(unsigned int n)
{
	unsigned int	i;
	unsigned int	n2;
	char			*ret;

	i = 0;
	n2 = n;
	while (n > 10)
	{
		i++;
		n = n / 10;
	}
	i++;
	ret = malloc(sizeof(char) * (i + 1));
	ret[i] = '\0';
	i--;
	while (n2 > 10)
	{
		ret[i] = (n2 % 10) + '0';
		n2 = n2 / 10;
		i--;
	}
	ret[0] = n2 + '0';
	return (ret);
}

void	dollar_pars(t_token *token, unsigned int *i)
{
	if (token->word[*i + 1] && token->word[*i + 1][0] == '?')
		switch_es(token, *i);
	else if (*i > 0 && *i + 1 >= token->tlen && token->type[*i - 1] == WORD)
	{
		token->word[*i - 1] = ft_strjoin(token->word[*i - 1], "$", true);
		erased_str(token, i);
	}
	else if (*i + 1 >= token->tlen && (*i == 0 || token->type[*i - 1] != WORD))
	{
		token->type[*i] = WORD;
	}
	else
	{
		pars_dollar(token, *i);
	}
	*i -= 1;
}
