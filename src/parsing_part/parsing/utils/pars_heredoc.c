/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:46:58 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/10 09:39:02 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_heredoc(t_token *token, unsigned int i)
{
	if (token->type[i + 1] && token->type[i + 1] == DOLLAR)
		token->type[i + 1] = WORD;
	else if (token->type[i + 1] && token->type[i + 2]
		&& token->type[i + 1] == SEP && token->type[i + 2] == DOLLAR)
		token->type[i + 2] = WORD;
}
