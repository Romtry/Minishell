/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erased_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 08:56:01 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/27 08:57:02 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erased_str(t_token *token, unsigned int *s)
{
	char			**temp;
	unsigned int	i;
	unsigned int	i2;

	i = -1;
	token->tlen--;
	if (token->tlen == 0)
	{
		token->err = 1;
		return ;
	}
	temp = malloc(sizeof(char *) * (token->tlen + 1));
	while (++i < *s)
		temp[i] = ft_strcpy(token->word[i]);
	i2 = i;
	i++;
	while (token->word[i])
		temp[i2++] = ft_strcpy(token->word[i++]);
	temp[i2] = NULL;
	free_word(token);
	token->word = temp;
	get_type(token, *s, *s);
	if (*s > 0)
		*s -= 1;
}

void	erased_str2(t_token *token, unsigned int s)
{
	char			**temp;
	unsigned int	i;
	unsigned int	i2;

	i = -1;
	token->tlen--;
	if (token->tlen == 0)
	{
		token->err = 1;
		return ;
	}
	temp = malloc(sizeof(char *) * (token->tlen + 1));
	while (++i < s)
		temp[i] = ft_strcpy(token->word[i]);
	i2 = i;
	i++;
	while (token->word[i])
		temp[i2++] = ft_strcpy(token->word[i++]);
	temp[i2] = NULL;
	free_word(token);
	token->word = temp;
	get_type(token, s, s);
	if (s > 0)
		s -= 1;
}
