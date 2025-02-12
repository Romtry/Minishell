/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:39:49 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 13:53:21 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
	token->type[i] = WORD;
}
