/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:19:35 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:19:44 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	if (token->word)
	{
		free_word(token);
		free(token->type);
		token->type = NULL;
		if (token->envhead)
			free_env(token->envhead);
	}
}
