/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:34:52 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:44:02 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_type(t_token *token, unsigned int one, unsigned int *temp)
{
	if (token->type[one] == DQUOTE)
		temp[one] = DQUOTED;
	else if (token->type[one] == SQUOTE)
		temp[one] = SQUOTED;
}
