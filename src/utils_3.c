/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:34:52 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/26 10:50:46 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_type(t_token *token)
{
	unsigned int	type;
	unsigned int	i;

	i = 0;
	token->type = malloc(sizeof(int) * (token->tlen + 1));
	while (token->word[i])
	{
		type = wich_type(token->word[i][0]);
		token->type[i] = type;
		i++;
	}
	token->type[i] = '\0';
}
