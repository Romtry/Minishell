/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:12:16 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:12:35 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	malloc_word(t_token *token, char *input, unsigned int c)
{
	unsigned int	i;
	unsigned int	save;

	i = 0;
	save = wich_type(input[0]);
	while (input[i] && save == wich_type(input[i]))
		i++;
	token->word[c] = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (input[i] && save == wich_type(input[i]))
	{
		token->word[c][i] = input[i];
		i++;
	}
	token->type[c] = save;
	token->word[c][i] = '\0';
	return (i);
}
