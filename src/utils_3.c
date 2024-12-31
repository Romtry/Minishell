/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:34:52 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/30 14:51:04 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_type(t_token *token)
{
	unsigned int	type;
	unsigned int	i;
	unsigned int	i2;

	i = 0;
	i2 = 0;
	token->type = malloc(sizeof(int) * (token->tlen + 1));
	while (token->word[i])
	{
		type = wich_type(token->word[i][0]);
		while (token->word[i][i2])
		{
			if (type != wich_type(token->word[i][i2])
				|| wich_type(token->word[i][i2]) == WORD)
			{
				type = WORD;
				break;
			}
			i2++;
		}
		i2 = 0;
		token->type[i] = type;
		i++;
	}
	token->type[i] = '\0';
}
