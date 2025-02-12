/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:20:13 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:41:09 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	realloc_word(t_token *token, unsigned int *one, unsigned int two)
{
	unsigned int	i2;
	unsigned int	i;
	char			**temp;

	i = -1;
	token->tlen -= (two - *one);
	temp = malloc(sizeof(char *) * (token->tlen + 1));
	while (++i < *one)
		temp[i] = ft_strcpy(token->word[i]);
	i2 = i++;
	temp[i2] = ft_strcpy(token->word[i]);
	while (++i < two)
		temp[i2] = ft_strjoin(temp[i2], token->word[i]);
	while (token->word[++i])
		temp[++i2] = ft_strcpy(token->word[i]);
	temp[i2 + 1] = NULL;
	free_word(token);
	token->word = temp;
	get_type(token, *one, two);
}
