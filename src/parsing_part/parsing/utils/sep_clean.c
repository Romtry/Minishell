/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:22:21 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:22:38 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sep_clean(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->word[i])
	{
		if (token->type[i] == SEP)
			erased_str(token, &i);
		i++;
	}
}
