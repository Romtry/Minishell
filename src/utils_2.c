/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:20:13 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/23 15:07:39 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_strcmp(char *str, char *str2)
{
	unsigned int	i;
	unsigned int	n;

	n = ft_strlen(str2);
	i = 0;
	while (str[i] && str[i] == str2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (1);
}

void	free_token(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->word[i])
	{
		free(token->word[i]);
		i++;
	}
	free(token->word);
	free(token->type);
}
