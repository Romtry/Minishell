/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:28:54 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:29:11 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
