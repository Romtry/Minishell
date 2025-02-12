/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:19:57 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:20:06 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_word(t_token *token)
{
	unsigned int	i;

	i = 0;
	if (token->word)
	{
		while (token->word[i])
		{
			free(token->word[i]);
			i++;
		}
		free(token->word);
		token->word = NULL;
	}
}
