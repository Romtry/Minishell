/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_es.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:28:15 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 13:53:52 by rothiery         ###   ########.fr       */
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
		token->word[i] = num_char(token->exit_stat);
		token->word[i] = ft_strjoin(token->word[i], temp, true);
		free(temp);
	}
	else
	{
		free(token->word[i]);
		token->word[i] = num_char(token->exit_stat);
	}
	if (i > 0 && token->type[i - 1] == WORD)
	{
		token->word[i - 1] = ft_strjoin(token->word[i - 1], token->word[i], true);
		erased_str(token, &i);
	}
}
