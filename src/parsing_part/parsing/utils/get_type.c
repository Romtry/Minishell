/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:43:44 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:43:51 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_type(t_token *token, unsigned int one, unsigned int two)
{
	unsigned int	i;
	unsigned int	i2;
	unsigned int	*temp;

	i = -1;
	temp = malloc(sizeof(unsigned int) * (token->tlen + 1));
	while (token->word[++i] && i < one)
		temp[i] = token->type[i];
	if (one != two)
	{
		quote_type(token, one, temp);
		i2 = i + 1;
	}
	else
		i2 = i;
	i = two + 1;
	while (token->word[i2])
	{
		temp[i2] = token->type[i];
		i2++;
		i++;
	}
	temp[i2] = '\0';
	free(token->type);
	token->type = temp;
}
