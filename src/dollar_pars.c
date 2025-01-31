/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:39:49 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/28 11:47:12 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	dollar_quote(t_token *token, unsigned int i)
{
	t_env	*list;

	list = token->envhead;
	token->type[i] = WORD;
	while (list)
	{
		if (ft_strcmp(list->name, (token->word[i] + 1)) == 0)
		{
			free(token->word[i]);
			token->word[i] = ft_strcpy(list->value);
			return ;
		}
		list = list->next;
	}
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
		token->word[i - 1] = ft_strjoin(token->word[i - 1], "$");
	else if (token->type[i + 1] == DQUOTED || token->type[i + 1] == SQUOTED)
		token->word[i + 1] = ft_strjoin2("$", token->word[i + 1]);
	erased_str(token, &i);
	token->type[i] = WORD;
}

void	dollar_pars(t_token *token, unsigned int *i, unsigned int *exit_stat)
{
	if (token->word[*i + 1] && token->word[*i + 1][0] == '?')
	{
		token->err = 1;
		printf("%u\n", *exit_stat);
		free_token(token);
		*exit_stat = 0;
	}
	else if (*i > 0 && *i + 1 >= token->tlen && token->type[*i - 1] == WORD)
	{
		token->word[*i - 1] = ft_strjoin(token->word[*i - 1], "$");
		erased_str(token, i);
	}
	else if (*i + 1 >= token->tlen && (*i == 0 || token->type[*i - 1] != WORD))
		token->type[*i] = WORD;
	else
		pars_dollar(token, *i);
	*i -= 1;
}
